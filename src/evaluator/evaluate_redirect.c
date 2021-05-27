/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:06:39 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/25 19:51:05 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
/*
static int	rdct_op_or_cmds(t_ast *cmds)
{
	if (cmds->op)
	{
		evaluate_redirect(cmds);
		return (EXIT_SUCCESS);
	}
	else
	{
		if (cmds->type == 1)
		{
			evaluate_builtin(cmds);
			return (EXIT_SUCCESS);
		}
		else if (cmds->type == 2)
		{
			execve(cmds->bin, cmds->av, g_sh->envp);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
*/
void	parent_fork(int pid)
{
	sig_child(pid);
	signal(SIGINT, sig_child);
	signal(SIGQUIT, sig_child);
	waitpid(pid, &g_sh->last_status, 0);
	signal(SIGINT, sigint_shell);
	signal(SIGQUIT, sigquit_shell);
	g_sh->last_status = WEXITSTATUS(g_sh->last_status);
}

static void	stdin_to_bin(t_ast *op)
{
	int	fd;
	int	pid;

	tcsetattr(0, 0, &g_sh->old_term);
	pid = fork();
	if (pid)
		parent_fork(pid);
	else
	{
		fd = open(op->right->bin, O_RDONLY);
		close(0);
		dup(fd);
		//rdct_op_or_cmds(op->left);
		op_or_cmds(op->left);
		close(fd);
	}
	tcsetattr(0, 0, &g_sh->new_term);
}

static void	stdout_to_file(t_ast *op)
{
	int	fd;
	int	pid;

	tcsetattr(0, 0, &g_sh->old_term);
	pid = fork();
	if (pid)
		parent_fork(pid);
	else
	{
		fd = open(op->right->bin, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(1);
		dup(fd);
		//rdct_op_or_cmds(op->left);
		op_or_cmds(op->left);
		close(fd);
	}
	tcsetattr(0, 0, &g_sh->new_term);
}

static void	stdout_to_eof(t_ast *op)
{
	int		fdpip[2];
	int		fd;
	char	buf;
	int		pid;

	tcsetattr(0, 0, &g_sh->old_term);
	pipe(fdpip);
	pid = fork();
	if (pid)
	{
		fd = open(op->right->bin, O_APPEND | O_WRONLY);
		if (fd < 1)
			fd = open(op->right->bin, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(fdpip[1]);
		parent_fork(pid);
		while (read(fdpip[0], &buf, 1))
			write(fd, &buf, 1);
		close(fd);
	}
	else
	{
		close(fdpip[0]);
		close(1);
		dup(fdpip[1]);
		//rdct_op_or_cmds(op->left);
		op_or_cmds(op->left);
	}
	tcsetattr(0, 0, &g_sh->new_term);
}

static void	stdout_to_stdin(t_ast *op)
{
	int fd[2];
	int	pid;

	tcsetattr(0, 0, &g_sh->old_term);
	pipe(fd);
	pid = fork();
	if (pid)
		parent_fork(pid);
	else
	{
		tcsetattr(0, 0, &g_sh->old_term);
		pid = fork();
		if (pid)
		{
			close(fd[1]);
			close(0);
			dup(fd[0]);
			parent_fork(pid);
			//rdct_op_or_cmds(op->right);
			op_or_cmds(op->left);
		}
		else
		{
			close(fd[0]);
			close(1);
			dup(fd[1]);
			//rdct_op_or_cmds(op->left);
			op_or_cmds(op->left);
		}
		tcsetattr(0, 0, &g_sh->new_term);
	}
	tcsetattr(0, 0, &g_sh->new_term);
}

void	evaluate_redirect(t_ast *op)
{
	if (op->op == 1)
		stdin_to_bin(op);
	else if (op->op == 2)
		stdout_to_file(op);
	else if (op->op == 3)
		stdout_to_eof(op);
	else
		stdout_to_stdin(op);
}
