/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 00:42:57 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/02 16:38:10 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	calc_pos(t_coords *c, long cursor, long size)
{
	c->lc = size % c->len;
	if (!c->ll)
		c->lc = size % (c->len - PROMPT_LEN);
	c->ll += (size / c->len) + (c->lc != 0);
	c->cc = cursor % c->len;
	if (!c->cl)
		c->cc = cursor % (c->len - PROMPT_LEN);
	c->cl += (cursor / c->len) + (c->cc != 0);
	if (c->ll)
		c->ll--;
	if (c->cl)
		c->cl--;
}

t_coords	cursor_position(void)
{
	t_coords	c;
	long		size;
	long		cursor;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_sh->events->ws);
	c.len = g_sh->events->ws.ws_col;
	size = g_sh->line_size;
	cursor = g_sh->line_cursor;
	c.ll = 0;
	if (size > (c.len - PROMPT_LEN))
	{
		size -= (c.len - PROMPT_LEN);
		c.ll = 1;
	}
	c.cl = 0;
	if (cursor > (c.len - PROMPT_LEN))
	{
		cursor -= (c.len - PROMPT_LEN);
		c.cl = 1;
	}
	calc_pos(&c, cursor, size);
	return (c);
}

void	clear_line(void)
{
	t_coords	c;

	jump_sides((char []){27, 91, 72, 0});
	ft_putstr_fd(g_sh->events->sc, 0);
	ft_putstr_fd(g_sh->events->ce, 0);
	c = cursor_position();
	while (c.cl < c.ll)
	{
		ft_putstr_fd(tgetstr("do", NULL), 0);
		ft_putstr_fd(g_sh->events->ce, 0);
		c.cl++;
	}
	ft_putstr_fd(g_sh->events->rc, 0);
}
