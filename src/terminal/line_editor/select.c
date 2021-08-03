/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:24:57 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/03 12:52:10 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	ctr + a
*/

int	ft_select(void)
{
	if (g_sh->select_start == -1
		|| (g_sh->select_start != -1 && g_sh->select_end != -1))
	{
		g_sh->select_start = g_sh->line_cursor;
		if (g_sh->select_end != -1)
			g_sh->select_end = -1;
		return (0);
	}
	if (g_sh->select_end == -1)
		g_sh->select_end = g_sh->line_cursor;
	g_sh->select_direction = 0;
	clear_line();
	ft_putstr_fd(g_sh->events->sc, 0);
	ft_putstr_fd(g_sh->line, 0);
	ft_putstr_fd(g_sh->events->rc, 0);
	return (0);
}

void	move_select(int direction)
{
	if (g_sh->line_cursor == g_sh->select_start)
		g_sh->select_direction = 0;
	if (g_sh->select_direction == 0)
		g_sh->select_direction = direction;
	ft_putstr_fd(g_sh->events->sc, 0);
	if (g_sh->select_start != -1 && g_sh->select_end == -1)
	{
		if (direction == g_sh->select_direction)
			ft_putstr_fd(REVER, 0);
		ft_putchar_fd(g_sh->line[g_sh->line_cursor], 0);
		ft_putstr_fd(E0M,0);
	}
	ft_putstr_fd(g_sh->events->rc, 0);
}
