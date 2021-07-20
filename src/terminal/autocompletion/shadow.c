/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 18:24:29 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/20 20:22:46 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	insert_shadow(void)
{
	size_t		size;

	if (g_sh->shadow && g_sh->shadow->cmd && g_sh->line)
	{
		size = ft_strlen(g_sh->line);
		ft_putstr_fd(g_sh->events->ce, 0);
		free(g_sh->line);
		g_sh->line = ft_strdup(g_sh->shadow->cmd);
		g_sh->line_cursor = ft_strlen(g_sh->line);
		ft_putstr_fd(&g_sh->shadow->cmd[size], 0);
		g_sh->shadow = NULL;
	}
	g_sh->shadow = NULL;
	return (0);
}

void history_shadow(void)
{
	t_history	*h;
	size_t		size;

	size = ft_strlen(g_sh->line);
	ft_putstr_fd(g_sh->events->ce, 0);
	h = g_sh->history;
	while (h)
	{
		if (g_sh->line && h->cmd && !ft_strncmp(g_sh->line, h->cmd, size))
		{
			ft_putstr_fd(g_sh->events->sc, 0);
			ft_putstr_fd(YELLOW, 0);
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
