/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:54:43 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/30 18:03:21 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	check_buffer(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] && ((31 < buf[i] && buf[i] < 127) || buf[i] == 10))
	{
		if (buf[i] != '\n')
			g_sh->line_cursor++;
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			return (3);
		}
		if (buf[++i] == 0)
			return (1);
	}
	return (0);
}

/*
**	ascii
**	4 = EOT
**	127 = DEL
*/

int	keys_event(char *buf)
{
	int	mcursor;

	if (buf[0] == 4)
		sh_exit(NULL);
	mcursor = move_cursor(buf);
	if (mcursor != 42)
		return (mcursor);
	if (!ft_strcmp(g_sh->events->up, buf) || !ft_strcmp(g_sh->events->dw, buf))
		return (browse_history(buf));
	if (ft_strlen(buf) == 1 && buf[0] == 12)
		return (ctrl_l());
	if (ft_strlen(buf) == 1 && buf[0] == 9)
		return (auto_complete());
	return (check_buffer(buf));
}
