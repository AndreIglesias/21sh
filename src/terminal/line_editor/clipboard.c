/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:23:54 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/03 17:43:17 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	g_copy[] = {27, 99, 0};
static char	g_paste[] = {27, 118, 0};
static char	g_cut[] = {27, 120, 0};

static int	ft_copy(void)
{
	long	a;
	long	b;

	if (g_sh->select_start != -1 && g_sh->select_end != -1)
	{
		if (g_sh->clip)
			free(g_sh->clip);
		a = g_sh->select_start;
		b = g_sh->select_end;
		if (a > b)
		{
			a = g_sh->select_end;
			b = g_sh->select_start;
		}
		g_sh->clip = ft_strndup(&g_sh->line[a], b - a);
	}
	return (0);
}

static int	ft_paste(void)
{
	if (g_sh->clip)
	{
		write_input(g_sh->clip);
	}
	return (0);
}

static int	ft_cut(void)
{
	return (0);
}

int	clipboard(char *buf)
{
	if (!ft_strcmp(g_copy, buf))
		return (ft_copy());
	if (!ft_strcmp(g_paste, buf))
		return (ft_paste());
	if (!ft_strcmp(g_cut, buf))
		return (ft_cut());

	return (42);
}
