/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:43:03 by jiglesia          #+#    #+#             */
/*   Updated: 2020/10/27 19:48:53 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_sqrt(double n)
{
	int		decimals;
	double	before;
	double	res;

	if (n <= 0)
		return (0);
	decimals = 0;
	res = n / 2;
	while (decimals != 5)
	{
		before = res;
		res = (res + n / res) / 2;
		if ((int)res == (int)before)
			decimals++;
	}
	return (res);
}
