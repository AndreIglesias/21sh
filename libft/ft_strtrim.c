/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 21:52:49 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/06 20:11:30 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_verif(char c, char const *set)
{
	int	i;

	i = 0;
	if (c && set)
		while (set && set[i])
			if (c == set[i++])
				return (1);
	return (0);
}

static int	ft_countrev(char const *s, char const *set)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!s)
		return (0);
	str = ft_strdup(s);
	if (!str)
		return (0);
	j = ft_strlen(s);
	while (str[i])
		str[i++] = s[--j];
	while (ft_verif(str[j], set))
		j++;
	return (i - j);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		i;
	int		j;
	int		a;
	char	*str;

	if (!s || !set)
		return (NULL);
	i = 0;
	while (ft_verif(s[i], set))
		i++;
	j = ft_countrev(&s[i], set);
	str = (char *)malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	a = 0;
	while (a < j)
		str[a++] = s[i++];
	str[a] = 0;
	return (str);
}
