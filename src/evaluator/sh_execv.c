/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 00:51:32 by jiglesia          #+#    #+#             */
/*   Updated: 2021/07/24 20:05:35 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sh_execv(char *name, char **av)
{
	char	str[200];

	save_envp(g_sh->ev, str, 0);
	if (!av)
		execve(name, (char *[]){name, NULL}, g_sh->envp);
	else
		execve(name, av, g_sh->envp);
	if (g_sh->envp)
	{
		ft_freesplit(g_sh->envp);
		g_sh->envp = NULL;
	}
}

void	xcmd(char *cmd[])
{
	int		pid;

	pid = fork();
	if (pid)
		parent_fork(pid);
	else
	{
		sh_execv(cmd[0], cmd);
		sh_exit(NULL);
	}
}

void	xcmd2(char *cmd[])
{
	int		pid;
	int		fd;

	pid = fork();
	if (pid)
		parent_fork(pid);
	else
	{

		fd = open("/dev/null", O_WRONLY);
		dup2(fd, 2);
		close(fd);
		sh_execv(cmd[0], cmd);
		sh_exit(NULL);
	}
}

char	*xbuff(char *cmd[], int nl)
{
	int		pid;
	int		pipefd[2];
	char	*line;

	pipe(pipefd);
	pid = fork();
	line = NULL;
	if (pid)
	{
		close(pipefd[1]);
		while (get_next_line(pipefd[0], &line) > 0 && nl-- > 0);
		return (line);
	}
	else
	{
		close(pipefd[0]);
		pipefd[0] = open("/dev/null", O_WRONLY);
		dup2(pipefd[0], 2);
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		sh_execv(cmd[0], cmd);
		sh_exit(NULL);
	}
	return (line);
}
