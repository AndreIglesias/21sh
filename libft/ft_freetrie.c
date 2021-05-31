/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetrie.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:38:17 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/21 15:50:39 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freetrie(t_trie **root)
{
	int		i;

	if (!(*root)->children)
	{
		delete_node(root);
		return ;
	}
	i = 0;
	while (i < 127)
	{
		if ((*root)->children && (*root)->map[i])
		{
			ft_freetrie(&(*root)->map[i]);
			(*root)->children--;
		}
		i++;
	}
	delete_node(root);
	return ;
}
