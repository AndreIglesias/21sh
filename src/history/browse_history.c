/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:49:04 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/20 16:56:50 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	change_history(t_shell *sh, char *str)
{
	int	i;

	i = sh->line_cursor;
	while (i-- > 0)
		ft_putstr_fd(sh->events->lf, 0);
	ft_putstr_fd(sh->events->ce, 0);
	sh->line = str;
	sh->line_cursor = ft_strlen(sh->line);
	ft_putstr(sh->line);
}

static void	browse_up(t_shell *sh)
{
	if (sh->history_cursor == sh->history && sh->line_tmp == NULL)
	{
		if (sh->line)
			sh->line_tmp = sh->line;
		else
			sh->line_tmp = ft_strdup("");
		change_history(sh, ft_strdup(sh->history_cursor->cmd));
		return ;
	}
	if (sh->history_cursor->next)
	{
		sh->history_cursor = sh->history_cursor->next;
		free(sh->line);
		change_history(sh, ft_strdup(sh->history_cursor->cmd));
	}
}

static void	browse_dw(t_shell *sh)
{
	if (sh->history_cursor == sh->history && sh->line_tmp)
	{
		change_history(sh, sh->line_tmp);
		sh->line_tmp = NULL;
		return ;
	}
	if (sh->history_cursor->back)
	{
		sh->history_cursor = sh->history_cursor->back;
		free(sh->line);
		change_history(sh, ft_strdup(sh->history_cursor->cmd));
	}
}

int	browse_history(t_shell *sh, char *buf)
{
	if (!ft_strcmp(sh->events->up, buf) && sh->history_cursor)
	{
		browse_up(sh);
		return (0);
	}
	else if (!ft_strcmp(sh->events->dw, buf) && sh->history_cursor)
		browse_dw(sh);
	return (0);
}
