/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 21:37:39 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/01 01:55:15 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	g_del[] = {27, 91, 51, 126, 0};
static char	g_cu[] = {27, 91, 49, 59, 53, 65, 0};
static char	g_cd[] = {27, 91, 49, 59, 53, 66, 0};
static char	g_cr[] = {27, 91, 49, 59, 53, 67, 0};
static char	g_cl[] = {27, 91, 49, 59, 53, 68, 0};
static char	g_home[] = {27, 91, 72, 0};
static char	g_end[] = {27, 91, 70, 0};

int	move_cursor(char *buf)
{
	g_sh->line_size = ft_strlen(g_sh->line);
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
		else if (!ft_strcmp(g_sh->events->rg, buf) && g_sh->shadow)
			return (insert_shadow());
		else if (!ft_strcmp(g_sh->events->lf, buf)
			|| !ft_strcmp(g_sh->events->rg, buf))
			return (move_arrows(buf));
	}
	else if (g_sh->line && g_sh->line[0])
	{
		if (g_sh->line_cursor > 0 && buf[0] == 127)
			return (delete_key());
		else if (g_sh->line_cursor < g_sh->line_size && !ft_strcmp(g_del, buf))
			return (revdel_key());
	}
	return (42);
}
