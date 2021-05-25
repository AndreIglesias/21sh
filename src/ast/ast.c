/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 21:26:00 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/25 20:10:45 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** type (1, cmd) (2, op)
** op (1, <) (2, >) (3, >>) (4, |)
*/

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
	new->valid = 1;
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
	new->op = op;
	return (new);
}
