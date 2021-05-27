/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:12:15 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/26 19:26:35 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	delete_astnode(t_ast *node)
{
	int		i;

	if (node->back)
		node->back->next = node->next;
	if (node->next)
		node->next->back = node->back;
	if (node->bin)
		free(node->bin);
	if (node->av)
	{
		i = 0;
		while (i < node->ac)
			free(node->av[i++]);
		free(node->av);
	}
	free(node);
}

void	free_ast(void)
{
	int		x;
	t_ast	*tmp;

	if (g_sh->cmds)
	{
		x = 0;
		while (g_sh->cmds[x])
		{
			tmp = first_in_list(g_sh->cmds[x], -1);
			if (tmp)
			{
				while (tmp->next)
				{
					tmp = tmp->next;
					delete_astnode(tmp->back);
				}
				delete_astnode(tmp);
			}
			g_sh->cmds[x] = NULL;
			x++;
		}
	}
}

void	free_cmd_line(void)
{
	int	i;

	if (g_sh->cmd_line)
	{
		i = 0;
		while (i < g_sh->ncmd)
		{
			if (g_sh->cmd_line[i])
				free(g_sh->cmd_line[i++]);
		}
		free(g_sh->cmd_line);
		g_sh->cmd_line = NULL;
	}
}
