/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:56:23 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/06 20:23:07 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_realloc(char *bowl)
{
	char		*dup;
	int			i;

	i = -1;
	dup = ft_strdup(bowl);
	if (bowl)
		free(bowl);
	bowl = (char *)malloc(sizeof(char) * (ft_strlen(dup) + BUFFER_SIZE + 1));
	if (!bowl)
		return (NULL);
	while (dup[++i])
		bowl[i] = dup[i];
	bowl[i] = 0;
	if (dup)
		free(dup);
	return (bowl);
}

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
