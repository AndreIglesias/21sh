/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 00:42:57 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/30 21:42:57 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_coords	cursor_position(void)
{
	t_coords	c;
	long		size;
	long		cursor;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_sh->events->ws);
	c.len = g_sh->events->ws.ws_col;
	size = g_sh->line_size;
	cursor = g_sh->line_cursor;
	c.ll = 0;
	if (size > (c.len - PROMPT_LEN))
	{
		size -= (c.len - PROMPT_LEN);
		c.ll = 1;
	}
	c.cl = 0;
	if (cursor > (c.len - PROMPT_LEN))
	{
		cursor -= (c.len - PROMPT_LEN);
		c.cl = 1;
	}

	c.lc = size % c.len;
	if (!c.ll)
		c.lc = size % (c.len - PROMPT_LEN);
	c.ll += (size / c.len) + (c.lc != 0);

	c.cc = cursor % c.len;
	if (!c.cl)
		c.cc = cursor % (c.len - PROMPT_LEN);
	c.cl += (cursor / c.len) + (c.cc != 0);
	return (c);
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

static int	next_space(char *str, int i)
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

static int	next_char(char *str, int i)
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
