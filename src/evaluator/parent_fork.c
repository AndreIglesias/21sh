/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 21:52:52 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/30 19:29:43 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	append_create_fd(int fdpip, t_ast *op)
{
	char	buf;
	int		fd;

	fd = open(op->right->bin, O_APPEND | O_WRONLY);
	if (fd < 1)
		fd = open(op->right->bin, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (read(fdpip, &buf, 1))
		write(fd, &buf, 1);
	close(fd);
}

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

static void	add_pid(int pid)
{
	t_ast	*tmp;

	tmp = new_astop(0);
	tmp->ac = pid;
	add_ast(&g_sh->pid, tmp);
}

static void	rm_pid(int pid)
{
	t_ast	*tmp;

	tmp = g_sh->pid;
	while (tmp)
	{
		if (tmp->ac == pid)
		{
			if (!tmp->next && !tmp->back)
				g_sh->pid = NULL;
			delete_astnode(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

void	parent_fork(int pid)
{
	add_pid(pid);
	signal(SIGINT, sig_child);
	signal(SIGQUIT, sig_child);
	waitpid(pid, &g_sh->last_status, 0);
	rm_pid(pid);
	signal(SIGINT, sigint_shell);
	signal(SIGQUIT, sigquit_shell);
	g_sh->last_status = WEXITSTATUS(g_sh->last_status);
}
