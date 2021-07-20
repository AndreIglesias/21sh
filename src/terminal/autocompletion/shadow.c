/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 18:24:29 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/20 19:57:59 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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
			break ;
		}
		h = h->next;
	}
}
