/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:04:34 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/25 18:56:23 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*extract_param(t_ast *tmp)
{
	char	*str;

	str = ft_strdup(tmp->bin);
	delete_astnode(tmp);
	return (str);
}

static t_ast	*add_param(t_ast *cmd, int c)
{
	t_ast	*tmp;

	tmp = cmd->next;
	while (tmp && tmp->bin)
	{
		c++;
		tmp = tmp->next;
	}
	if (c)
	{
		cmd->av = ft_memalloc(sizeof(char *) * (c + 2));
		cmd->ac = c + 1;
		c = 1;
		tmp = cmd->next;
		while (tmp && tmp->bin)
		{
			cmd->av[c++] = extract_param(tmp);
			tmp = tmp->next;
		}
		return (tmp);
	}
	cmd->av = ft_memalloc(sizeof(char *) * 2);
	cmd->ac = 1;
	return (tmp);
}

static void	construct_cmds(t_ast **head)
{
	t_ast	*tmp;
	t_ast	*n;

	tmp = *head;
	while (tmp)
	{
		if (tmp->bin)
		{
			n = add_param(tmp, 0);
			if (tmp->av)
				tmp->av[0] = ft_strdup(tmp->bin);
			tmp = n;
		}
		else
			tmp = tmp->next;
	}
}

int	ft_parser(int x)
{
	t_ast	*tree;

	construct_cmds(&g_sh->cmds[x]);
	tree = construct_tree(&g_sh->cmds[x], NULL, NULL, 0);
	if (!tree)
		return (EXIT_FAILURE);
	g_sh->cmds[x] = tree;
	return (EXIT_SUCCESS);
}
