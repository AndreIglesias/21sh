/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 18:24:29 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/29 00:52:27 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	reset_shadow(void)
{
	size_t	cursor;

	if (g_sh->shadow && g_sh->shadow->cmd)
	{
		ft_putstr_fd(g_sh->events->sc, 0);
		cursor = g_sh->line_cursor;
		while (cursor++ < g_sh->line_size - 1)
			ft_putstr_fd(g_sh->events->rg, 0);
		ft_putstr_fd(g_sh->events->ce, 0);
		ft_putstr_fd(g_sh->events->rc, 0);
	}
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

static void	put_shadow(size_t size, size_t cursor, t_history *h)
{
	long	col;
	long	llines;
	long	cllines;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_sh->events->ws);
	col = g_sh->events->ws.ws_col - PROMPT_LEN;
	llines = (size / col) + (size % col != 0);
	cllines = (cursor / col) + (cursor % col != 0);
	if (llines == cllines)
	{
		ft_putstr_fd(g_sh->events->sc, 0);
		while ((long)cursor % col < (long)size % col)
		{
			ft_putstr_fd(g_sh->events->rg, 0);
			cursor++;
		}
		ft_putstr_fd(LIGHT_GRAY, 0);
		while (h->cmd[size] && (long)size != col && (long)size % col < col - 1)
			ft_putchar_fd(h->cmd[size++], 0);
		ft_putstr_fd(E0M, 0);
		ft_putstr_fd(g_sh->events->rc, 0);
		g_sh->shadow = h;
	}
}

void	history_shadow(void)
{
	t_history	*h;
	size_t		size;

	reset_shadow();
	g_sh->line_size = ft_strlen(g_sh->line);
	size = g_sh->line_size;
	h = g_sh->history;
	while (size && h)
	{
		if (g_sh->line && h->cmd && !ft_strncmp(g_sh->line, h->cmd, size))
		{
			put_shadow(size, g_sh->line_cursor, h);
			return ;
		}
		h = h->next;
	}
	g_sh->shadow = NULL;
}
