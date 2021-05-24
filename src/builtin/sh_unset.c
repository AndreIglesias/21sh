/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 23:46:17 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/24 23:25:38 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sh_unset(int argc, char **key)
{
	t_trie	**tmp;

	if (argc == 2)
	{
		tmp = delete_value(&g_sh->ev, key[1], ft_strlen(key[1]), 0);
		if (!tmp)
		{
			ft_putstr_fd(BOLD"minishell: unset: ", 2);
			ft_putstr_fd("invalid parameter name"E0M, 2);
			ft_putchar_fd('\n', 2);
		}
	}
}
