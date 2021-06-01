/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 21:09:56 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/01 01:55:47 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int			i;
	char		*dup;

	if (s)
	{
		i = 0;
		while (s[i])
			i++;
		dup = (char *)malloc(sizeof(char) * (i + 1));
		if (!dup)
			return (NULL);
		i = 0;
		while (s[i])
		{
			dup[i] = (char)s[i];
			i++;
		}
		dup[i] = 0;
		return (dup);
	}
	return (NULL);
}
