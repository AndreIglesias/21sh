/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_counttil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 01:02:08 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/04 01:04:51 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_counttil(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
		if (s[i++] == c)
			break ;
	if (i)
		return (i - 1);
	else
		return (0);
}
