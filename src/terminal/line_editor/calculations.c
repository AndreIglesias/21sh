/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 22:26:06 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/31 22:26:37 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	next_space(char *str, int i)
{
	int	my_space;

	if (str && str[i - 1])
	{
		my_space = 0;
		i--;
		if (str[i] == ' ')
			my_space = 1;
		while (i && (str[i] != ' ' || my_space))
		{
			if (str[i] != ' ')
				my_space = 0;
			i--;
		}
		if (!my_space && str[i] == ' ')
			i++;
	}
	return (i);
}

int	next_char(char *str, int i)
{
	int	my_char;

	if (str && str[i])
	{
		my_char = 0;
		i++;
		if (str[i] != ' ')
			my_char = 1;
		while (str[i] && (str[i] == ' ' || my_char))
		{
			if (str[i] == ' ')
				my_char = 0;
			i++;
		}
	}
	return (i);
}
