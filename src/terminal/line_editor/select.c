/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:24:57 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/03 01:19:58 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	ctr + a
*/

int	ft_select(void)
{
	if (g_sh->select_start == -1
		|| (g_sh->select_start != -1 && g_sh->select_end != -1))
	{
		g_sh->select_start = g_sh->line_cursor;
		if (g_sh->select_end != -1)
			g_sh->select_end = -1;
		return (0);
	}
	ft_putstr("end_selection");
	if (g_sh->select_end == -1)
		g_sh->select_end = g_sh->line_cursor;
	return (0);
}
