/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:20:31 by jiglesia          #+#    #+#             */
/*   Updated: 2019/10/31 15:13:21 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst1;
	unsigned char		*src1;
	size_t				i;

	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	i = 1;
	if (dst1 > src1)
	{
		while (i <= len)
		{
			dst1[len - i] = src1[len - i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			*(dst1++) = *(src1++);
	}
	return (dst);
}
