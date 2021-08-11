/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:23:54 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/11 06:10:03 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	ft_paste(void)
{
	//long	len;
	if (g_sh->clip)
	{
		write_input(g_sh->clip);
		g_sh->select_start = -1;
		/*len = ft_strlen(g_sh->clip) + 1;
		while (len-- > 0)
		{
			if (move_arrows(g_sh->events->rg) == 2)
				ft_putstr_fd(g_sh->events->rg, 0);
				}*/
	}
	return (0);
}

static int	ft_cut(void)
{
	g_sh->select_start = -1;
	return (0);
}

/*
**	copy = ctrl + b
**	paste = ctrl + v
**	cut = ctrl + x
*/

int	clipboard(char *buf)
{
	if (buf[0] == 22)
		return (ft_paste());
	if (buf[0] == 24)
		return (ft_cut());

	return (42);
}
