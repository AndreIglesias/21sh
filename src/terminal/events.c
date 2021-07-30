/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 19:17:16 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/30 19:08:39 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	jump_sides(char *buf)
{
	if (buf[2] == 70 && g_sh->line_cursor < ft_strlen(g_sh->line))
	{
		while (g_sh->line_cursor < ft_strlen(g_sh->line))
		{
			ft_putstr_fd(g_sh->events->rg, 0);
			g_sh->line_cursor++;
		}
	}
	if (buf[2] == 72 && g_sh->line_cursor)
	{
		while (g_sh->line_cursor)
		{
			ft_putstr_fd(g_sh->events->lf, 0);
			g_sh->line_cursor--;
		}
	}
	return (0);
}

int	ctrl_l(void)
{
	long	i;

	xcmd((char *[]){"/usr/bin/clear", NULL});
	ft_prompt();
	ft_putstr_fd(g_sh->line, 0);
	i = ft_strlen(g_sh->line);
	while (i > g_sh->line_cursor)
	{
		ft_putstr_fd(g_sh->events->lf, 0);
		i--;
	}
	return (0);
}
