/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 23:36:58 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/22 11:05:57 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	sh_echo(char **value, t_uchar flag)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (value[i])
	{
		a += ft_putstr(value[i++]);
		a += ft_putstr(" ");
	}
	if (flag)
		return (a);
	a += write(1, "\n", 1);
	return (a);
}
