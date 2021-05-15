/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 20:51:06 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/06 19:53:02 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_newlist(void *data, size_t size)
{
	t_list	*list;

	list = NULL;
	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (list);
	if (data)
	{
		list->data = data;
		list->size = size;
	}
	else
	{
		list->data = NULL;
		list->size = 0;
	}
	list->next = NULL;
	return (list);
}
