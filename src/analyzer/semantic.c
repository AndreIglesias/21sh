/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 00:00:07 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/24 00:19:37 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	consistent_types(t_ast *node, char *str)
{
	int		i;

	i = 1;
	if (node)
	{
		if (node->bin)
		{
			if (is_builtin(node->bin))
				node->type = 1;
			else
			{
				str = sh_which(node->bin, g_sh->ev);
				if (str)
				{
					node->type = 2;
					free(node->bin);
					node->bin = str;
				}
				else
					return (0);
			}
		}
		i *= consistent_types(node->left, NULL);
		i *= consistent_types(node->right, NULL);
	}
	return (i);
}

int	ft_semantic(int x)
{
	if (!consistent_types(g_sh->cmds[x], NULL))
		return ((int)ft_puterror(BOLD"semantic error command/file type \
mismatch\n"E0M, (void *)EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
