/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newlisti.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 22:16:34 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/07 22:21:38 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_listi	*ft_newlisti(int data, size_t size)
{
	t_listi	*list;

	list = NULL;
	list = (t_listi *)malloc(sizeof(t_listi));
	if (!list)
		return (list);
	if (data)
	{
		list->n = data;
		list->size = size;
	}
	else
	{
		list->n = 0;
		list->size = 0;
	}
	list->next = NULL;
	return (list);
}
