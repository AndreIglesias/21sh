/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:49:04 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/29 12:16:40 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	change_history(char *str)
{
	int	i;

	i = g_sh->line_cursor;
	while (i-- > 0)
		ft_putstr_fd(g_sh->events->lf, 0);
	ft_putstr_fd(g_sh->events->ce, 0);
	g_sh->line = str;
	g_sh->line_cursor = ft_strlen(g_sh->line);
	ft_putstr(g_sh->line);
}

static void	browse_up(void)
{
	if (g_sh->history_cursor == g_sh->history && g_sh->line_tmp == NULL)
	{
		if (g_sh->line)
			g_sh->line_tmp = g_sh->line;
		else
		{
			if (g_sh->line_tmp)
				free(g_sh->line_tmp);
			g_sh->line_tmp = ft_strdup("");
		}
		change_history(ft_strdup(g_sh->history_cursor->cmd));
		return ;
	}
	if (g_sh->history_cursor->next)
	{
		g_sh->history_cursor = g_sh->history_cursor->next;
		free(g_sh->line);
		change_history(ft_strdup(g_sh->history_cursor->cmd));
	}
}

static void	browse_dw(void)
{
	if (g_sh->history_cursor == g_sh->history && g_sh->line_tmp)
	{
		if (g_sh->line)
			free(g_sh->line);
		change_history(g_sh->line_tmp);
		g_sh->line_tmp = NULL;
		return ;
	}
	if (g_sh->history_cursor->back)
	{
		g_sh->history_cursor = g_sh->history_cursor->back;
		free(g_sh->line);
		change_history(ft_strdup(g_sh->history_cursor->cmd));
	}
}

int	browse_history(char *buf)
{
	if (!ft_strcmp(g_sh->events->up, buf) && g_sh->history_cursor)
	{
		browse_up();
		return (0);
	}
	else if (!ft_strcmp(g_sh->events->dw, buf) && g_sh->history_cursor)
		browse_dw();
	return (0);
}
