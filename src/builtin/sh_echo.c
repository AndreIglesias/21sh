/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 23:36:58 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/24 16:35:56 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	sh_echo(int	argc, char **value)
{
	int	i;
	int	a;
	int	flag;

	a = 0;
	if (argc >= 1)
	{
		flag = 0;
		if (argc > 1)
			if (!ft_strcmp(value[1], "-n"))
				flag = 1;
		i = 1 + flag;
		while (value[i])
		{
			a += ft_putstr(value[i++]);
			a += ft_putstr(" ");
		}
		if (flag)
			return (a);
		a += write(1, "\n", 1);
	}
	return (a);
}
