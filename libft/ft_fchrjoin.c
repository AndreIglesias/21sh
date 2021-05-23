/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fchrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:24:39 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/21 18:53:38 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_fchrjoin(char *s1, char s2)
{
	char	*str;
	int		a;

	if (s2 == '\0')
		return (NULL);
	if (s1 == NULL)
	{
		str = ft_memalloc(sizeof(char) * (2));
		if (!str)
			return (NULL);
		str[0] = s2;
		return (str);
	}
	str = ft_memalloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!str)
		return (NULL);
	a = 0;
	while (s1[a])
	{
		str[a] = s1[a];
		a++;
	}
	str[a++] = s2;
	free(s1);
	return (str);
}
