/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:04:34 by ciglesia          #+#    #+#             */
/*   Updated: 2021/06/04 18:31:57 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*extract_param(t_ast **tmp)
{
	char	*str;
	t_ast	*del;

	str = ft_strdup((*tmp)->bin);
	del = *tmp;
	*tmp = (*tmp)->next;
	delete_astnode(del);
	return (str);
}

static t_ast	*add_param(t_ast *cmd, int c, int ls)
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
		cmd->av = ft_memalloc(sizeof(char *) * (c + 2 + ls));
		cmd->ac = c + 1 + ls;
		c = 1 + ls;
		tmp = cmd->next;
		while (tmp && tmp->bin)
		{
			if (cmd->av[c])
				free(cmd->av[c]);
			cmd->av[c++] = extract_param(&tmp);
		}
		return (tmp);
	}
	cmd->av = ft_memalloc(sizeof(char *) * (2 + ls));
	cmd->ac = 1 + ls;
	return (tmp);
}

static void	collect_args(t_ast **tmp, t_ast **the_cmd)
{
	t_ast	*n;
	t_uchar	ls;

	ls = 0;
	if (!ft_strcmp((*tmp)->bin, "ls") && LS)
		ls = 1;
	n = add_param((*tmp), 0, ls);
	if ((*tmp)->av[0])
		free((*tmp)->av[0]);
	(*tmp)->av[0] = ft_strdup((*tmp)->bin);
	if (ls)
		(*tmp)->av[1] = ft_strdup("--color=auto");
	*the_cmd = (*tmp);
	(*tmp) = n;
}

static void	construct_cmds(t_ast **head, t_ast *the_cmd)
{
	t_ast	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->bin && !the_cmd)
			collect_args(&tmp, &the_cmd);
		else if (tmp->bin && the_cmd && tmp->back->bin)
			the_cmd->av = ft_avjoin(the_cmd->av, &the_cmd->ac,
					extract_param(&tmp));
		else
		{
			if (tmp->op == 4)
				the_cmd = NULL;
			else if (tmp->op && the_cmd == NULL && tmp->next
				&& tmp->next->next && tmp->next->next->bin)
				tmp = tmp->next;
			tmp = tmp->next;
		}
	}
}

int	ft_parser(int x)
{
	t_ast	*tree;

	if (!g_sh->cmds[x])
		return (EXIT_SUCCESS);
	construct_cmds(&g_sh->cmds[x], NULL);
	tree = construct_tree(&g_sh->cmds[x], NULL, NULL, 0);
	if (!tree)
		return (EXIT_FAILURE);
	g_sh->cmds[x] = tree;
	return (EXIT_SUCCESS);
}
