/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:54:43 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/20 00:56:25 by ciglesia         ###   ########.fr       */
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

static void	del_ins(t_shell *sh)
{
	if (sh->line_cursor == ft_strlen(sh->line))
		sh->line[ft_strlen(sh->line) - 1] = 0;
	else
	{
		sh->line[sh->line_cursor - 1] = 0;
		sh->line = ft_strjoin(sh->line, &sh->line[sh->line_cursor]);
		ft_putstr_fd(&sh->line[sh->line_cursor - 1], 0);
	}
}

static void	change_history(t_shell *sh)
{
	int	i;

	i = sh->line_cursor;
	while (i-- > 0)
		ft_putstr_fd(sh->events->lf, 0);
	ft_putstr_fd(sh->events->ce, 0);
}

int	browse_history(t_shell *sh,char *buf)
{


	if (!ft_strcmp(sh->events->up, buf) && sh->history_cursor->next)
	{
		change_history(sh);
		free(sh->line);
		sh->history_cursor = sh->history_cursor->next;
		sh->line = ft_strdup(sh->history_cursor->cmd);
		sh->line_cursor = ft_strlen(sh->line);
		ft_putstr(sh->line);
		return (0);
	}
	else if (!ft_strcmp(sh->events->dw, buf) && sh->history_cursor->back)
	{
		change_history(sh);
		free(sh->line);
		sh->history_cursor = sh->history_cursor->back;
		sh->line = ft_strdup(sh->history_cursor->cmd);
		sh->line_cursor = ft_strlen(sh->line);
		ft_putstr(sh->line);
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
	if (buf[0] == 127 && sh->line && sh->line[0] && sh->line_cursor > 0)
	{
		ft_putstr_fd(sh->events->lf, 0);
		ft_putstr_fd(sh->events->sc, 0);
		ft_putstr_fd(sh->events->ce, 0);
		del_ins(sh);
		ft_putstr_fd(sh->events->rc, 0);
		sh->line_cursor--;
		return (2);
	}
	if (!ft_strcmp(sh->events->up, buf) || !ft_strcmp(sh->events->dw, buf))
		return (browse_history(sh, buf));
	if (!ft_strcmp(sh->events->lf, buf) || !ft_strcmp(sh->events->rg, buf))
		return (move_cursor(sh, buf));
	if (ft_strlen(buf) == 1 && buf[0] != 127 && buf[0] != 8 && buf[0] != 12)
	{
		if (buf[0] != '\n')
			sh->line_cursor++;
		return (1);
	}
	return (0);
}
