/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:50:20 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/06 18:39:20 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*empty_string(void)
{
	char	*p;

	p = (char *)malloc(sizeof(char));
	if (!p)
		return (NULL);
	p[0] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*str;
	unsigned int		i;

	i = 0;
	if (s && start >= ft_strlen(s))
		return (empty_string());
	if (!s)
		return (NULL);
	str = (char *)ft_calloc(sizeof(char), len + 1);
	if (!str)
		return (NULL);
	if (*s && ft_strlen(s) > start)
	{
		while (s[start] && len-- > 0)
			str[i++] = (char)s[start++];
		str[i] = 0;
	}
	return (str);
}
