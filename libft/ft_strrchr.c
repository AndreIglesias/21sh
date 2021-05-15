/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 21:26:46 by jiglesia          #+#    #+#             */
/*   Updated: 2019/10/24 16:31:57 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	char		a;

	i = 0;
	a = (char)c;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i--] == a)
			return ((char *)s + ++i);
	}
	return (NULL);
}
