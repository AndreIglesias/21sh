/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 19:36:41 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/19 20:01:21 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *bowl, size_t size)
{
	char		*dup;
	int			i;

	i = -1;
	dup = ft_strdup(bowl);
	if (bowl)
		free(bowl);
	bowl = (char *)malloc(sizeof(char) * (ft_strlen(dup) + size + 1));
	if (!bowl)
		return (NULL);
	while (dup[++i])
		bowl[i] = dup[i];
	bowl[i] = 0;
	if (dup)
		free(dup);
	return (bowl);
}
