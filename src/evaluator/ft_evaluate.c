/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_evaluate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:33:44 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/01 01:40:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	exec_cmd(t_ast *cmds)
{
	int	pid;

	tcsetattr(0, 0, &g_sh->old_term);
	pid = fork();
	if (pid)
		parent_fork(pid);
	else
	{
		if (cmds->right)
			stdin_to_bin(cmds);
		else
			sh_execv(cmds->bin, cmds->av);
		sh_exit(NULL);
	}
	tcsetattr(0, 0, &g_sh->new_term);
	return (EXIT_SUCCESS);
}

int	op_or_cmds(t_ast *cmds)
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
			return (exec_cmd(cmds));
	}
	return (EXIT_FAILURE);
}

static void	add_str(char *str, char *value)
{
	int		i;
	char	**dup;

	i = 0;
	while (g_sh->envp && g_sh->envp[i])
		i++;
	dup = g_sh->envp;
	g_sh->envp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (dup && dup[i])
	{
		g_sh->envp[i] = dup[i];
		i++;
	}
	if (dup)
		free(dup);
	g_sh->envp[i++] = ft_strjoin(str, value);
	g_sh->envp[i] = NULL;
}

void	save_envp(t_trie *root, char *str, int lvl)
{
	int		i;

	if (root->end)
	{
		str[lvl] = '=';
		str[lvl + 1] = 0;
		add_str(str, root->value);
		return ;
	}
	i = 0;
	while (i < 127)
	{
		if (root->children && root->map[i])
		{
			str[lvl] = (char)i;
			str[lvl + 1] = 0;
			save_envp(root->map[i], str, lvl + 1);
		}
		i++;
	}
}

void	ft_evaluate(void)
{
	int		i;

	i = 0;
	while (i < g_sh->ncmd)
	{
		if (g_sh->cmds && g_sh->cmds[i] && g_sh->cmds[i]->valid)
			op_or_cmds(g_sh->cmds[i]);
		i++;
	}
}
