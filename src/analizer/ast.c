/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 21:26:00 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/23 19:52:31 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** type (1, cmd) (2, op)
** op (1, <) (2, >) (3, >>) (4, |)
*/

void	delete_astnode(t_ast *node)
{
	int	i;

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
}

t_ast	**new_astvec(int size)
{
	t_ast	**new;
	int		i;

	new = malloc(sizeof(t_ast *) * (size + 1));
	if (!new)
		return (ft_puterror(BOLD"minishell: malloc error\n"E0M, NULL));
	i = 0;
	while (i < size + 1)
		new[i++] = NULL;
	return (new);
}

static t_ast	*init_ast(void)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (ft_puterror(BOLD"minishell: malloc error\n"E0M, NULL));
	new->next = NULL;
	new->back = NULL;
	new->type = 0;
	new->left = NULL;
	new->right = NULL;
	new->bin = NULL;
	new->av = NULL;
	new->ac = 0;
	new->op = 0;
	return (new);
}

t_ast	*new_astcmd(char *cmd, char **av)
{
	t_ast	*new;
	int		i;

	new = init_ast();
	new->type = 1;
	new->bin = cmd;
	new->av = av;
	if (av)
	{
		i = 0;
		while (av[i])
			i++;
		new->ac = i;
	}
	else
		new->ac = 0;
	return (new);
}

t_ast	*new_astop(t_uchar op)
{
	t_ast	*new;

	new = init_ast();
	new->type = 2;
	new->op = op;
	return (new);
}
