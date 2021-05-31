/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 23:36:58 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/30 16:14:56 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	sh_echo(int	argc, char **value)
{
	int	i;
	int	j;
	int	a;
	int	flag;

	a = 0;
	if (argc >= 1)
	{
		flag = 0;
		i = 1;
		while (argc > 1 && value[i][0] == '-')
		{
			j = 1;
			while (value[i][j] == 'n')
			{
				j++;
				if (value[i][j] == '\0')
					flag = 1;
			}
			if (value[i][j])
				break ;
			i++;
		}
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
