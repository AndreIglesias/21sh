/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 21:13:34 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/06 19:58:03 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	a;

	a = ft_strlen(dest);
	i = a;
	j = 0;
	if (size)
	{
		while (i < size - 1 && src[j])
			dest[i++] = src[j++];
	}
	dest[i] = '\0';
	if (size < a)
		return (size + ft_strlen(src));
	return (a + ft_strlen(src));
}
