/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:42:26 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/28 18:24:36 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	s1 = dst
**	s2 = to insert
**	pos = position
*/

static char	*valid(char *s1, char const *s2)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	return (s1);
}

char	*ft_strins(char *s1, char const *s2, size_t pos)
{
	size_t		a;
	char		*str;

	if (!s1 || !s2)
		return (valid(s1, s2));
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	a = 0;
	while (s1[a] && a < pos)
	{
		str[a] = s1[a];
		a++;
	}
	str[a] = 0;
	str = ft_strcat(str, s2);
	if (a == pos)
		str = ft_strcat(str, &s1[a]);
	free(s1);
	return (str);
}
