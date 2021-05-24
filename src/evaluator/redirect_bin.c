/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:20:03 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/23 13:09:49 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	stdin_to_bin(t_ast *op)
{
	t_ast	*cmd;
	int		fd;

	cmd = op->left;
	if (!fork())
	{
		fd = open(op->right->bin, O_RDONLY);
		close(0);
		dup(fd);
		execve(cmd->bin, cmd->av, arbol(ev));
		close(fd);
	}
	else
		wait(NULL);
}

void	bin_stdout_to_file(t_ast *op)
{
	t_ast	*cmd;
	int		fd;

	if (!fork())
	{
		fd = open(op->right->bin, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(1);
		dup(fd);
		execv(name, argv);
		close(fd);
	}
	else
		wait(NULL);
}

void	bin_stdout_to_eof(t_ast *op)
{
	t_ast	*cmd;
	int		fdpip[2];
	int		fd;

	pipe(fdpip);
	if (!fork())
	{
		close(fdpip[0]);
		close(1);
		dup(fdpip[1]);
		execv(name, argv);
	}
	else
	{
		fd = open(op->right->bin, O_APPEND | O_WRONLY);
		if (fd < 1)
			fd = open(op->right->bin, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(fdpip[1]);
		wait(NULL);
		while (read(fd2[0], &buf, 1))
			write(fd, &buf, 1);
		close(fd);
	}
}

void	stdout_to_stdin(t_ast *op)
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
			execv(op->left->left->bin, op->left->left->av);
		}
		else
		{
			close(fd[1]);
			close(0);
			dup(fd[0]);
			wait(NULL);
			execv(op->left->bin, op->left->av);
		}
	}
	else
		wait(NULL);
}
