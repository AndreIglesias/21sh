/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:54:43 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/21 00:09:18 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	move_cursor(char *buf)
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

static void	del_ins(void)
{
	if (g_sh->line_cursor == ft_strlen(g_sh->line))
		g_sh->line[ft_strlen(g_sh->line) - 1] = 0;
	else
	{
		g_sh->line[g_sh->line_cursor - 1] = 0;
		g_sh->line = ft_fstrjoin(g_sh->line, &g_sh->line[g_sh->line_cursor]);
		ft_putstr_fd(&g_sh->line[g_sh->line_cursor - 1], 0);
	}
}

static int	delete_key(void)
{
	reset_shadow();
	ft_putstr_fd(g_sh->events->lf, 0);
	ft_putstr_fd(g_sh->events->sc, 0);
	ft_putstr_fd(g_sh->events->ce, 0);
	del_ins();
	ft_putstr_fd(g_sh->events->rc, 0);
	g_sh->line_cursor--;
	if (g_sh->line_cursor)
		history_shadow();
	return (2);
}

static int	check_buffer(char *buf)
{
	int	i;

	reset_shadow();
	i = 0;
	while (buf[i] && ((31 < buf[i] && buf[i] < 127) || buf[i] == 10))
	{
		if (buf[i] != '\n')
			g_sh->line_cursor++;
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			return (3);
		}
		if (buf[++i] == 0)
			return (1);
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
	static char	right[] = {27, 91, 67, 0};

	if (buf[0] == 4)
		sh_exit(NULL);
	if (ft_strlen(buf) == 6 && (!ft_strcmp(cl, buf) || !ft_strcmp(cr, buf)))
		return (move_ctrl(buf, cl, cr));
	if (ft_strlen(buf) == 3 && (!ft_strcmp(home, buf) || !ft_strcmp(end, buf)))
		return (jump_sides(buf));
	if (ft_strlen(buf) == 3 && !ft_strcmp(right, buf) && g_sh->shadow)
		return (insert_shadow());
	if (buf[0] == 127 && g_sh->line && g_sh->line[0] && g_sh->line_cursor > 0)
		return (delete_key());
	if (!ft_strcmp(g_sh->events->up, buf) || !ft_strcmp(g_sh->events->dw, buf))
		return (browse_history(buf));
	if (!ft_strcmp(g_sh->events->lf, buf) || !ft_strcmp(g_sh->events->rg, buf))
		return (move_cursor(buf));
	if (ft_strlen(buf) == 1 && buf[0] == 12)
		return (ctrl_l());
	if (ft_strlen(buf) == 1 && buf[0] == 9)
		return (auto_complete());
	return (check_buffer(buf));
}
