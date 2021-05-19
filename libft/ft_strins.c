/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:42:26 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/19 18:13:59 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	s1 = dst
**	s2 = to insert
**	pos = position
*/

static char	*valid(char const *s1, char const *s2)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	return (ft_strdup(s1));
}

char	*ft_strins(char const *s1, char const *s2, size_t pos)
{
	size_t		i;
	size_t		a;
	size_t		save;
	char		*str;

	if (!s1 || !s2)
		return (valid(s1, s2));
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	a = 0;
	while (s1[a] && a < pos)
	{
		str[a] = s1[a];
		a++;
	}
	save = a;
	i = 0;
	while (s2[i])
		str[a++] = s2[i++];
	while (s1[save])
		str[a++] = s1[save++];
	str[a] = 0;
	return (str);
}
