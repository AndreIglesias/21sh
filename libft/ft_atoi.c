/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 20:31:09 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/06 18:43:19 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	a;
	int	b;

	i = 0;
	b = 0;
	while (nptr[i] && (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
			|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == '\v'))
		i++;
	if (nptr[i] == '-')
	{
		a = -1;
		i++;
	}
	else if (nptr[i] == '+')
	{
		i++;
		a = 1;
	}
	else
		a = 1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		b = ((b * 10) + (a * (nptr[i++] - '0')));
	return (b);
}
