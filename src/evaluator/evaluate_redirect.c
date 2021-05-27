/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:06:39 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/27 18:58:17 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	cat_last_file(t_ast *cmds)
{
	t_ast	*tmp;

	if (cmds)
	{
		tmp = cmds;
		while (tmp->left)
			tmp = tmp->left;
		op_or_cmds(tmp);
	}
}

void	add_pid(int pid)
{
	t_ast	*tmp;

	tmp = new_astop(0);
	tmp->ac = pid;
	add_ast(&g_sh->pid, tmp);
}

void	parent_fork(int pid)
{
	add_pid(pid);
	signal(SIGINT, sig_child);
	signal(SIGQUIT, sig_child);
	waitpid(pid, &g_sh->last_status, 0);
	sig_child(pid);
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
		op_or_cmds(op->left);
		if (op->left->op)
			cat_last_file(op->left);
		close(fd);
		sh_exit(NULL);
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
		op_or_cmds(op->left);
		if (op->left->op)
			cat_last_file(op->left);
		close(fd);
		sh_exit(NULL);
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
		close(fdpip[1]);
		parent_fork(pid);
		fd = open(op->right->bin, O_APPEND | O_WRONLY);
		if (fd < 1)
		fd = open(op->right->bin, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		while (read(fdpip[0], &buf, 1))
			write(fd, &buf, 1);
		close(fd);
	}
	else
	{
		close(fdpip[0]);
		close(1);
		dup(fdpip[1]);
		op_or_cmds(op->left);
		if (op->left->op)
			cat_last_file(op->left);
		sh_exit(NULL);
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
	{
		parent_fork(pid);
		close(fd[1]);
		close(0);
		dup(fd[0]);
		op_or_cmds(op->right);
	}
	else
	{
		close(fd[0]);
		close(1);
		dup(fd[1]);
		op_or_cmds(op->left);
		if (op->left->op)
			cat_last_file(op->left);
		sh_exit(NULL);
	}
	tcsetattr(0, 0, &g_sh->new_term);
}

void	evaluate_redirect(t_ast *op)
{
	int	pid;

	if (op->op == 1)
		stdin_to_bin(op);
	else if (op->op == 2)
		stdout_to_file(op);
	else if (op->op == 3)
		stdout_to_eof(op);
	else
	{
		tcsetattr(0, 0, &g_sh->old_term);
		pid = fork();
		if (pid)
			parent_fork(pid);
		else
		{
			stdout_to_stdin(op);
			sh_exit(NULL);
		}
		tcsetattr(0, 0, &g_sh->new_term);
	}
}
