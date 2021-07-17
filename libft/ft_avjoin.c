/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avjoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 19:19:19 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/17 19:19:20 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_avjoin(char **av, int *ac, char *str)
{
	char	**new;
	int		i;

	if (av && *ac && str)
	{
		new = malloc(sizeof(char *) * (*ac + 2));
		i = 0;
		while (i < *ac)
		{
			new[i] = av[i];
			i++;
		}
		new[(*ac)++] = str;
		new[*ac] = NULL;
		free(av);
		return (new);
	}
	return (NULL);
}
