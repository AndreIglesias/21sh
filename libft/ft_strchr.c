/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 21:08:05 by jiglesia          #+#    #+#             */
/*   Updated: 2019/10/24 21:23:06 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int			i;
	char		a;

	i = 0;
	a = (char)c;
	while (s[i])
	{
		if (s[i++] == a)
			return ((char *)s + --i);
	}
	if (a == '\0')
		return ((char *)s + i);
	return (NULL);
}
