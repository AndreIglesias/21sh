/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 19:19:03 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/17 19:19:04 by ciglesia         ###   ########.fr       */
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
