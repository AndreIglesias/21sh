/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 23:36:58 by jiglesia          #+#    #+#             */
/*   Updated: 2021/07/28 23:44:09 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	put_echo(int i, char **value, int argc)
{
	while (i < argc)
	{
		ft_putstr(value[i]);
		if (i + 1 < argc)
			ft_putchar(' ');
		i++;
	}
}

void	sh_echo(int	argc, char **value)
{
	int	i;
	int	j;
	int	flag;

	if (argc >= 1)
	{
		flag = 0;
		i = 1;
		while (argc > 1 && i < argc && value[i][0] == '-')
		{
			j = 1;
			while (value[i][j] == 'n')
				if (value[i][++j] == '\0')
					flag = 1;
			if (value[i][j])
				break ;
			i++;
		}
		put_echo(i, value, argc);
		if (!flag)
			write(1, "\n", 1);
	}
	g_sh->last_status = 0;
}
