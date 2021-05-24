/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:06:39 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/24 12:29:33 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	stdin_to_bin(t_ast *op)
{
	int		fd;

	if (!fork())
	{
		fd = open(op->right->bin, O_RDONLY);
		close(0);
		dup(fd);
		op_or_cmds(op->left);
		//execve(cmd->bin, cmd->av, arbol(ev));
		close(fd);
	}
	else
		wait(NULL);
}

static void	bin_stdout_to_file(t_ast *op)
{
	int		fd;

	if (!fork())
	{
		fd = open(op->right->bin, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(1);
		dup(fd);
		op_or_cmds(op->left);
		//execv(name, argv);
		close(fd);
	}
	else
		wait(NULL);
}

static void	bin_stdout_to_eof(t_ast *op)
{
	int		fdpip[2];
	int		fd;
	char	buf;

	pipe(fdpip);
	if (!fork())
	{
		close(fdpip[0]);
		close(1);
		dup(fdpip[1]);
		op_or_cmds(op->left);
		//execv(name, argv);
	}
	else
	{
		fd = open(op->right->bin, O_APPEND | O_WRONLY);
		if (fd < 1)
			fd = open(op->right->bin, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(fdpip[1]);
		wait(NULL);
		while (read(fdpip[0], &buf, 1))
			write(fd, &buf, 1);
		close(fd);
	}
}

static void	stdout_to_stdin(t_ast *op)
{
	int fd[2];

	pipe(fd);
	if (!fork())
	{
		if (!fork())
		{
			close(fd[0]);
			close(1);
			dup(fd[1]);
			op_or_cmds(op->left);
			//execv(op->left->left->bin, op->left->left->av);
		}
		else
		{
			close(fd[1]);
			close(0);
			dup(fd[0]);
			wait(NULL);
			op_or_cmds(op->right);
			//execv(op->left->bin, op->left->av);
		}
	}
	else
		wait(NULL);
}

void	evaluate_redirect(t_ast *op)
{
	if (op->op == 1)
		stdin_to_bin(op);
	else if (op->op == 2)
		bin_stdout_to_file(op);
	else if (op->op == 3)
		bin_stdout_to_eof(op);
	else
		stdout_to_stdin(op);
}
