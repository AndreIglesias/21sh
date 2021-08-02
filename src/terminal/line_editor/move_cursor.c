/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:23:15 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/02 15:56:05 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	move_arrows(char *buf)
{
	t_coords	c0;

	reset_shadow();
	c0 = cursor_position();
	if (!ft_strcmp(g_sh->events->lf, buf) && g_sh->line_cursor)
	{
		g_sh->line_cursor--;
		if ((c0.cl && c0.cc == 0) || (!c0.cl && !c0.cc))
		{
			ft_putstr_fd(tgetstr("up", NULL), 0);
			ft_putstr_fd(tgoto(tgetstr("RI", NULL), 0, c0.len), 0);
			return (0);
		}
		return (2);
	}
	if (!ft_strcmp(g_sh->events->rg, buf) && g_sh->line_cursor
		< g_sh->line_size)
	{
		g_sh->line_cursor++;
		if ((!c0.cl && c0.cc == c0.len - PROMPT_LEN - 1)
				|| (c0.cl && c0.cc == c0.len - 1))
			ft_putstr_fd(tgetstr("do", NULL), 0);
		else
			return (2);
		return (0);
	}
	return (0);
}

/*
**	ctrl + direction[]
**	left | right
**	home | end
*/

static char	g_cu[] = {27, 91, 49, 59, 53, 65, 0};
static char	g_cd[] = {27, 91, 49, 59, 53, 66, 0};
static char	g_cr[] = {27, 91, 49, 59, 53, 67, 0};
static char	g_cl[] = {27, 91, 49, 59, 53, 68, 0};

void	move_vertically(char *buf)
{
	t_coords	c;
	long		up;
	long		dw;

	c = cursor_position();
	up = g_sh->line_cursor - (c.cc + (c.len - c.cc));
	dw = g_sh->line_cursor + (c.cc + (c.len - c.cc));
	if (!ft_strcmp(g_cu, buf) && c.cl > 0 && up >= 0)
	{
		g_sh->line_cursor = up;
		ft_putstr_fd(g_sh->events->up, 0);
	}
	else if (!ft_strcmp(g_cd, buf) && c.cl < c.ll && dw <= g_sh->line_size)
	{
		g_sh->line_cursor = dw;
		ft_putstr_fd(g_sh->events->dw, 0);
	}
}

int	move_ctrl(char *buf)
{
	long	x;

	if (!ft_strcmp(g_cl, buf) && g_sh->line_cursor)
	{
		x = next_space(g_sh->line, g_sh->line_cursor);
		while (x < g_sh->line_cursor)
		{
			if (move_arrows(g_sh->events->lf) == 2)
				ft_putstr_fd(g_sh->events->lf, 0);
		}
	}
	else if (!ft_strcmp(g_cr, buf) && g_sh->line_cursor < g_sh->line_size)
	{
		x = next_char(g_sh->line, g_sh->line_cursor);
		while (g_sh->line_cursor < x)
		{
			if (move_arrows(g_sh->events->rg) == 2)
				ft_putstr_fd(g_sh->events->rg, 0);
		}
	}
	else
		move_vertically(buf);
	return (0);
}

int	jump_sides(char *buf)
{
	//t_coords	c;

	if (buf[2] == 72 && g_sh->line_cursor)
	{
		while (0 < g_sh->line_cursor)
		{
			if (move_arrows(g_sh->events->lf) == 2)
				ft_putstr_fd(g_sh->events->lf, 0);
		}
	}
	if (buf[2] == 70 && g_sh->line_cursor < g_sh->line_size)
	{
		while (g_sh->line_cursor < g_sh->line_size)
		{
			if (move_arrows(g_sh->events->rg) == 2)
				ft_putstr_fd(g_sh->events->rg, 0);
		}
/*		c = cursor_position();
		if (c.cl != c.ll)
			ft_putstr_fd(tgoto(tgetstr("DO", NULL), 0, c.ll - c.cl), 0);
		if (c.ll)
		{
			if (!c.cl)
				c.cc += PROMPT_LEN;
			if (c.lc < c.cc)
				ft_putstr_fd(tgoto(tgetstr("LE", NULL), 0, c.cc - c.lc), 0);
			else if (c.cc < c.lc)
				ft_putstr_fd(tgoto(tgetstr("RI", NULL), 0, c.lc - c.cc), 0);
		}
		else
			ft_putstr_fd(tgoto(tgetstr("RI", NULL), 0, c.lc - c.cc), 0);
			g_sh->line_cursor = g_sh->line_size;*/
	}
	return (0);
}
