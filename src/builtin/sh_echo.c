/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 23:36:58 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/19 23:42:19 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	sh_echo(char *value, t_uchar flag)
{
	ft_putstr(value);
	if (flag)
		return (ft_strlen(value));
	write(1, "\n", 1);
	return (ft_strlen(value) + 1);
}
