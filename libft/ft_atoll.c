/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 18:05:01 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/01 12:50:45 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	check_last(long long b, char *nb, int i, int a)
{
	if (b == -922337203685477580)
	{
		if (nb[i] && !nb[i + 1] && nb[i] < '9')
			return (((b * 10) + (a * (nb[i++] - '0'))));
		else
			return (0);
	}
	else if (b == 922337203685477580)
	{
		if (nb[i] && !nb[i + 1] && nb[i] < '8')
			return (((b * 10) + (a * (nb[i++] - '0'))));
		else
			return (0);
	}
	if (nb[i] && !nb[i + 1])
		return (((b * 10) + (a * (nb[i++] - '0'))));
	return (0);
}

long long	ft_atoll(char *nb)
{
	int			i;
	int			a;
	long long	b;

	i = 0;
	b = 0;
	if (nb[i] == '-')
	{
		a = -1;
		i++;
	}
	else
		a = 1;
	if (nb[i] == '+')
		i++;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		if ((i == 18 && a == 1 && nb[0] != '+') || (i == 19
				&& (a == -1 || nb[0] == '+')))
			return (check_last(b, nb, i, a));
		b = ((b * 10) + (a * (nb[i++] - '0')));
	}
	return (b);
}
