/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 18:24:29 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/21 00:21:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	reset_shadow(void)
{
	int	i;

	ft_putstr_fd(g_sh->events->sc, 0);
	i = g_sh->line_cursor;
	while (i-- > 0)
		ft_putstr_fd(g_sh->events->lf, 0);
	ft_putstr_fd(g_sh->events->ce, 0);
	ft_putstr_fd(g_sh->line, 0);
	ft_putstr_fd(g_sh->events->rc, 0);
	g_sh->shadow = NULL;
}

int	insert_shadow(void)
{
	int			i;

	if (g_sh->shadow && g_sh->shadow->cmd && g_sh->line)
	{
		i = g_sh->line_cursor;
		while (i-- > 0)
			ft_putstr_fd(g_sh->events->lf, 0);
		ft_putstr_fd(g_sh->events->ce, 0);
		free(g_sh->line);
		g_sh->line = ft_strdup(g_sh->shadow->cmd);
		g_sh->line_cursor = ft_strlen(g_sh->line);
		ft_putstr_fd(g_sh->line, 0);
	}
	g_sh->shadow = NULL;
	return (0);
}

void	history_shadow(void)
{
	t_history	*h;
	size_t		size;
	size_t		i;

	size = ft_strlen(g_sh->line);
	h = g_sh->history;
	while (size && h)
	{
		if (g_sh->line && h->cmd && !ft_strncmp(g_sh->line, h->cmd, size))
		{
			ft_putstr_fd(g_sh->events->sc, 0);
			i = g_sh->line_cursor;
			while (i++ < size)
				ft_putstr_fd(g_sh->events->rg, 0);
			ft_putstr_fd(g_sh->events->ce, 0);
			ft_putstr_fd(LIGHT_GRAY, 0);
			ft_putstr_fd(&h->cmd[size], 0);
			ft_putstr_fd(E0M, 0);
			ft_putstr_fd(g_sh->events->rc, 0);
			g_sh->shadow = h;
			return ;
		}
		h = h->next;
	}
	g_sh->shadow = NULL;
}
