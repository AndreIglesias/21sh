/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:23:15 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/30 17:56:08 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

//int	reset_cursor(){}

static int	move_arrows(char *buf)
{
	reset_shadow();
	if (!ft_strcmp(g_sh->events->lf, buf) && g_sh->line_cursor)
	{
		g_sh->line_cursor--;
		return (2);
	}
	if (!ft_strcmp(g_sh->events->rg, buf) && g_sh->line_cursor
		< ft_strlen(g_sh->line))
	{
		g_sh->line_cursor++;
		return (2);
	}
	return (0);
}

static char	g_del[] = {27, 91, 51, 126, 0};
static char	g_cu[] = {27, 91, 49, 59, 53, 65, 0};
static char	g_cd[] = {27, 91, 49, 59, 53, 66, 0};
static char	g_cr[] = {27, 91, 49, 59, 53, 67, 0};
static char	g_cl[] = {27, 91, 49, 59, 53, 68, 0};
static char	g_home[] = {27, 91, 72, 0};
static char	g_end[] = {27, 91, 70, 0};

int	move_cursor(char *buf)
{
	if (ft_strlen(buf) == 6)
	{
		if (!ft_strcmp(g_cu, buf) || !ft_strcmp(g_cd, buf)
			||!ft_strcmp(g_cl, buf) || !ft_strcmp(g_cr, buf))
			return (move_ctrl(buf));
	}
	else if (ft_strlen(buf) == 3)
	{
		if (!ft_strcmp(g_home, buf) || !ft_strcmp(g_end, buf))
			return (jump_sides(buf));
		if (!ft_strcmp(g_sh->events->lf, buf)
			|| !ft_strcmp(g_sh->events->rg, buf))
			return (move_arrows(buf));
		if (!ft_strcmp(g_sh->events->rg, buf) && g_sh->shadow)
			return (insert_shadow());
	}
	else if (g_sh->line && g_sh->line[0])
	{
		if (g_sh->line_cursor > 0 && buf[0] == 127)
			return (delete_key());
		if (g_sh->line_cursor < g_sh->line_size && !ft_strcmp(g_del, buf))
			return (revdel_key());
	}
	return (42);
}
