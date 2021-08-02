/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 17:55:54 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/02 19:23:08 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	clear_next_lines(void)
{
	t_coords	c;

	ft_putstr_fd(g_sh->events->sc, 0);
	ft_putstr_fd(g_sh->events->ce, 0);
	c = cursor_position();
	while (c.cl < c.ll)
	{
		ft_putstr_fd(tgetstr("do", NULL), 0);
		ft_putstr_fd(g_sh->events->ce, 0);
		c.cl++;
	}
	ft_putstr_fd(g_sh->events->rc, 0);
}

int	delete_key(void)
{
	reset_shadow();
	ft_putstr_fd(g_sh->events->lf, 0);
	ft_putstr_fd(g_sh->events->sc, 0);
	clear_next_lines();
	if (g_sh->line_cursor == g_sh->line_size)
		g_sh->line[g_sh->line_size - 1] = 0;
	else
	{
		g_sh->line[g_sh->line_cursor - 1] = 0;
		g_sh->line = ft_fstrjoin(g_sh->line, &g_sh->line[g_sh->line_cursor]);
		ft_putstr_fd(&g_sh->line[g_sh->line_cursor - 1], 0);
	}
	ft_putstr_fd(g_sh->events->rc, 0);
	g_sh->line_cursor--;
	if (g_sh->line_cursor)
		history_shadow();
	return (2);
}

int	revdel_key(void)
{
	reset_shadow();
	ft_putstr_fd(g_sh->events->sc, 0);
	clear_next_lines();
	if (g_sh->line_cursor < g_sh->line_size)
	{
		g_sh->line[g_sh->line_cursor] = 0;
		g_sh->line = ft_fstrjoin(g_sh->line,
				&g_sh->line[g_sh->line_cursor + 1]);
		ft_putstr_fd(&g_sh->line[g_sh->line_cursor], 0);
	}
	ft_putstr_fd(g_sh->events->rc, 0);
	if (g_sh->line_cursor)
		history_shadow();
	return (2);
}
