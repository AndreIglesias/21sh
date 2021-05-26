/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:54:43 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/26 13:54:11 by ciglesia         ###   ########.fr       */
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

/*
**	ascii
**	4 = EOT
**	127 = DEL
*/

int	keys_event(char *buf)
{
	if (buf[0] == 4)
		sh_exit();
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
