/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 18:24:29 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/22 00:12:55 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	cursor_to_end(int crow, int ccol, int lrow, int lcol)
{
	crow = (ccol != 0);
	lrow = (lcol != 0);
	while (ccol != lcol)
	{
		if (ccol < lcol)
		{
			ft_putstr_fd(g_sh->events->rg, 0);
			ccol++;
		}
		else
		{
			ft_putstr_fd(g_sh->events->lf, 0);
			ccol--;
		}
	}
	while (crow < lrow)
	{
		ft_putstr_fd(g_sh->events->dw, 0);
		ccol++;
	}
}

void	reset_shadow(void)
{
	int		col;
	size_t	sshadow;
	int		trail;

	if (g_sh->shadow && g_sh->shadow->cmd)
	{
		col = g_sh->events->ws.ws_col;


		sshadow = ft_strlen(g_sh->shadow->cmd);//		shadow lenght (lines = lenght / ws_li)

		ft_putstr_fd(g_sh->events->sc, 0);//			save cursor
		cursor_to_end(g_sh->line_cursor / col, g_sh->line_cursor % col,
					  g_sh->line_size / col, g_sh->line_size % col);

		ft_putstr_fd(g_sh->events->ce, 0);
		trail = (int)(sshadow / col + sshadow % col) - (int)(g_sh->line_size / col);
		while (col-- > 0)
			ft_putstr_fd(g_sh->events->lf, 0);
		while (trail-- > 0)
		{
			ft_putstr_fd(g_sh->events->dw, 0);
			ft_putstr_fd(g_sh->events->ce, 0);
		}
		ft_putstr_fd(g_sh->events->rc, 0);//			reset horizontal cursor
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

void	history_shadow(void)
{
	t_history	*h;
	size_t		size;
	size_t		i;

	//reset_shadow();
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
			ioctl(STDIN_FILENO, TIOCGWINSZ, &g_sh->events->ws);
			return ;
		}
		h = h->next;
	}
	g_sh->shadow = NULL;
}
