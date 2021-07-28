/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 00:42:57 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/29 01:00:22 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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
	if (!ft_strcmp(g_cu, buf) && g_sh->prompt_y > 0)
	{
		ft_putstr_fd(tgetstr("up", NULL), 0);
		g_sh->prompt_y--;
	}
	else if (!ft_strcmp(g_cd, buf))
	{
		ft_putstr_fd(tgetstr("do", NULL), 0);
		g_sh->prompt_y++;
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
	size_t	x;

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
