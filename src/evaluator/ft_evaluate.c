/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_evaluate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:33:44 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/24 12:46:01 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	op_or_cmds(t_ast *cmds)
{
	if (cmds->op)
		evaluate_redirect(cmds);
	else
	{
		if (cmds->type == 0)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putstr_fd(cmds->bin, 2);
			ft_putstr_fd("\n",2);
		}
		else if (cmds->type == 1)
			evaluate_builtin(cmds);
		else if (cmds->type == 2)
			execve(cmds->bin, cmds->av, g_sh->envp);
		//evaluate_bin(cmds);
	}
}

void	add_str(char *str, char *value)
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
	g_sh->envp = NULL;
	char	str[200];
	int		i;

	i = 0;
	while (g_sh->cmds[i])
	{
		save_envp(g_sh->ev, str, 0);
		op_or_cmds(g_sh->cmds[i]);
		ft_freesplit(g_sh->envp);
		i++;
	}
}
