/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:04:34 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/23 20:28:10 by ciglesia         ###   ########.fr       */
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

static t_ast	*add_param(t_ast *cmd)
{
	t_ast	*tmp;
	int		c;

	c = 0;
	tmp = cmd->next;
	while (tmp && tmp->bin)
	{
		c++;
		tmp = tmp->next;
	}
	if (c)
	{
		cmd->av = ft_memalloc(sizeof(char *) * (c + 1));
		cmd->ac = c;
		c = 0;
		tmp = cmd->next;
		while (tmp && tmp->bin)
		{
			cmd->av[c++] = extract_param(tmp);
			tmp = tmp->next;
		}
	}
	return (tmp);
}

static void	construct_cmds(t_ast **head)
{
	t_ast	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->bin)
			tmp = add_param(tmp);
		else
			tmp = tmp->next;
	}
}

static int	consistent_operations(t_ast *node)
{
	int	i;

	i = 1;
	if (node)
	{
		if (!node->bin && (!node->right || !node->right->bin))
			return (0);
		i *= consistent_operations(node->left);
		i *= consistent_operations(node->right);
	}
	return (i);
}

int	ft_parser(int x)
{
	t_ast	*op;

	construct_cmds(&g_sh->cmds[x]);
	op = arrange_ast(g_sh->cmds[x], NULL, NULL);
	if (!consistent_operations(op))
		return ((int)ft_puterror(BOLD"syntax error inconsistent redirection\n"
							E0M, (void *)EXIT_FAILURE));
	print_tokens(g_sh->cmds[x], 0);
	if (op)
		g_sh->cmds[x] = op;
	print_btree(g_sh->cmds[x], "", 0);
	ft_putstr("\n");
	return (EXIT_SUCCESS);
}
