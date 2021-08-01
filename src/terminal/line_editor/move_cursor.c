/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:23:15 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/31 22:35:27 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

//int	reset_cursor(){}

int	move_arrows(char *buf)
{
	reset_shadow();
	if (!ft_strcmp(g_sh->events->lf, buf) && g_sh->line_cursor)
	{
		g_sh->line_cursor--;
		return (2);
	}
	if (!ft_strcmp(g_sh->events->rg, buf) && g_sh->line_cursor
		< ft_strlen(g_sh->line))
	{
		g_sh->line_cursor++;
		return (2);
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

	g_sh->line_size = ft_strlen(g_sh->line);
	c = cursor_position();
	up = g_sh->line_cursor - (c.cc + (c.len - c.cc));
	dw = g_sh->line_cursor + (c.cc + (c.len - c.cc));
	if (!ft_strcmp(g_cu, buf) && c.cl > 0 && up > 0)
	{
		g_sh->line_cursor = up;
		ft_putstr_fd(g_sh->events->up, 0);
	}
	else if (!ft_strcmp(g_cd, buf) && c.cl < c.ll && dw < g_sh->line_size)
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
			ft_putstr_fd(g_sh->events->lf, 0);
			g_sh->line_cursor--;
		}
	}
	else if (!ft_strcmp(g_cr, buf) && g_sh->line_cursor
		< ft_strlen(g_sh->line))
	{
		x = next_char(g_sh->line, g_sh->line_cursor);
		while (g_sh->line_cursor < x)
		{
			ft_putstr_fd(g_sh->events->rg, 0);
			g_sh->line_cursor++;
		}
	}
	else
		move_vertically(buf);
	return (0);
}

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
