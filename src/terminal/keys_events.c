/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:54:43 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/26 18:05:09 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	move_cursor(char *buf)
{
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

static void	del_ins(void)
{
	if (g_sh->line_cursor == ft_strlen(g_sh->line))
		g_sh->line[ft_strlen(g_sh->line) - 1] = 0;
	else
	{
		g_sh->line[g_sh->line_cursor - 1] = 0;
		g_sh->line = ft_strjoin(g_sh->line, &g_sh->line[g_sh->line_cursor]);
		ft_putstr_fd(&g_sh->line[g_sh->line_cursor - 1], 0);
	}
}

static int	delete_key()
{
	ft_putstr_fd(g_sh->events->lf, 0);
	ft_putstr_fd(g_sh->events->sc, 0);
	ft_putstr_fd(g_sh->events->ce, 0);
	del_ins();
	ft_putstr_fd(g_sh->events->rc, 0);
	g_sh->line_cursor--;
	return (2);
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

static int	move_ctrl(char *buf, char *cl, char *cr)
{
	size_t	x;

	if (!ft_strcmp(cl, buf) && g_sh->line_cursor)
	{
		x = next_space(g_sh->line, g_sh->line_cursor);
		while (x < g_sh->line_cursor)
		{
			ft_putstr_fd(g_sh->events->lf, 0);
			g_sh->line_cursor--;
		}
	}
	else if (!ft_strcmp(cr, buf) && g_sh->line_cursor
		< ft_strlen(g_sh->line))
	{
		x = next_char(g_sh->line, g_sh->line_cursor);
		while (g_sh->line_cursor < x)
		{
			ft_putstr_fd(g_sh->events->rg, 0);
			g_sh->line_cursor++;
		}
	}
	return (0);
}

static int	jump_sides(char *buf)
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

/*
**	ascii
**	4 = EOT
**	127 = DEL
*/

int	keys_event(char *buf)
{
	static char	cr[] = {27, 91, 49, 59, 53, 67, 0};
	static char	cl[] = {27, 91, 49, 59, 53, 68, 0};
	static char	home[] = {27, 91, 72, 0};
	static char	end[] = {27, 91, 70, 0};

	if (buf[0] == 4)
		sh_exit();
	if (ft_strlen(buf) == 6 && (!ft_strcmp(cl, buf) || !ft_strcmp(cr, buf)))
		return (move_ctrl(buf, cl, cr));
	if (ft_strlen(buf) == 3 && (!ft_strcmp(home, buf) || !ft_strcmp(end, buf)))
		return (jump_sides(buf));
	if (buf[0] == 127 && g_sh->line && g_sh->line[0] && g_sh->line_cursor > 0)
		return (delete_key());
	if (!ft_strcmp(g_sh->events->up, buf) || !ft_strcmp(g_sh->events->dw, buf))
		return (browse_history(buf));
	if (!ft_strcmp(g_sh->events->lf, buf) || !ft_strcmp(g_sh->events->rg, buf))
		return (move_cursor(buf));
	if (ft_strlen(buf) == 1 && ((31 < buf[0] && buf[0] < 127) || buf[0] == 10))
	{
		if (buf[0] != '\n')
			g_sh->line_cursor++;
		return (1);
	}
	return (0);
}
