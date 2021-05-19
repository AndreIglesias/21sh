/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:54:43 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/19 19:17:01 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	move_cursor(t_shell *sh, char *buf)
{
	if (!ft_strcmp(sh->events->lf, buf) && sh->line_cursor)
	{
		sh->line_cursor--;
		return (2);
	}
	if (!ft_strcmp(sh->events->rg, buf) &&
		sh->line_cursor < ft_strlen(sh->line))
	{
		sh->line_cursor++;
		return (2);
	}
	return (0);
}

/*
**	ascii
**	4 = EOT
**	127 = DEL
*/

int	keys_event(char *buf, t_shell *sh)
{
	if (buf[0] == 4)
		exit(0);
	if (buf[0] == 127 && sh->line && sh->line[0])
	{
		ft_putstr_fd(sh->events->lf, 0);
		ft_putstr_fd(sh->events->sc, 0);
		ft_putstr_fd(sh->events->ce, 0);
		ft_putstr_fd(sh->events->rc, 0);
		sh->line[ft_strlen(sh->line) - 1] = 0;// delete in position not the end
		sh->line_cursor--;
		return (2);
	}
	if (!ft_strcmp(sh->events->up, buf) || !ft_strcmp(sh->events->dw, buf))
		return (0);
	if (!ft_strcmp(sh->events->lf, buf) || !ft_strcmp(sh->events->rg, buf))
		return (move_cursor(sh, buf));
	if (ft_strlen(buf) == 1 && buf[0] != 127)
	{
		if (buf[0] != '\n')
			sh->line_cursor++;
		return (1);
	}
	return (0);
}
