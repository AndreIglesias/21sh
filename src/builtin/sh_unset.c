/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 23:46:17 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/24 12:51:11 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sh_unset(t_trie *ev, char *key)
{
	t_trie	**tmp;

	tmp = delete_value(&ev, key, ft_strlen(key), 0);
	if (!tmp)
	{
		ft_putstr_fd(BOLD"minishell: unset: ", 2);
		ft_putstr_fd("invalid parameter name"E0M, 2);
		ft_putchar_fd('\n', 2);
	}
}
