/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttrie.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:31:24 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/20 18:22:42 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puttrie(t_trie *root, char *str, int lvl)
{
	int		i;

	if (root->end)
	{
		str[lvl] = 0;
		ft_putstr(str);
		ft_putstr("=");
		ft_putstr(root->value);
		ft_putchar('\n');
		return ;
	}
	i = 0;
	while (i < 127)
	{
		if (root->children && root->map[i])
		{
			str[lvl] = (char)i;
			str[lvl + 1] = 0;
			ft_puttrie(root->map[i], str, lvl + 1);
		}
		i++;
	}
}
