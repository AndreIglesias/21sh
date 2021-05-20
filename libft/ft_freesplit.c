/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freesplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 19:50:17 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/20 12:07:55 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freesplit(char **split)
{
	int	i;

	i = 0;
	if (*split)
	{
		while (split[i])
			i++;
		while (i)
			free(split[--i]);
	}
	free(split);
	split = NULL;
}
