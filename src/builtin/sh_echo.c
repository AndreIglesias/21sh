/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 23:36:58 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/01 12:24:12 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	put_line_space(char *str)
{
	ft_putstr(str);
	ft_putchar(' ');
}

int	sh_echo(int	argc, char **value)
{
	int	i;
	int	j;
	int	flag;

	if (argc >= 1)
	{
		flag = 0;
		i = 1;
		while (argc > 1 && value[i][0] == '-')
		{
			j = 1;
			while (value[i][j++] == 'n')
				if (value[i][j] == '\0')
					flag = 1;
			if (value[i][j])
				break ;
			i++;
		}
		while (value[i])
			put_line_space(value[i++]);
		if (flag)
			return (EXIT_SUCCESS);
		write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
