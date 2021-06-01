/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:06:39 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/02 01:45:17 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	stdin_to_bin(t_ast *cmds)
{
	int		fd[2];
	t_ast	*tmp;
	int		pid;
	char	**argv;

	tcsetattr(0, 0, &g_sh->old_term);
	pipe(fd);
	pid = fork();
	if (pid)
	{
		parent_fork(pid);
		close(fd[1]);
		close(STDIN_FILENO);
		dup(fd[0]);
		sh_execv(cmds->bin, cmds->av);
	}
	else
	{
		tmp = cmds->right;
		close(fd[0]);
		close(STDOUT_FILENO);
		dup(fd[1]);
		while (tmp)
		{
			argv = str_to_arr("/bin/cat", tmp->right->bin);
			sh_execv("/bin/cat", argv);
			tmp = tmp->left;
			ft_freesplit(argv);
		}
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
	int		pid;

	tcsetattr(0, 0, &g_sh->old_term);
	pipe(fdpip);
	pid = fork();
	if (pid)
	{
		close(fdpip[1]);
		parent_fork(pid);
		append_create_fd(fdpip[0], op);
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
	int	fd[2];
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
		if (op->left->op && op->left->op != 4)
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
