/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:54:43 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/02 16:12:19 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	ctrl_l(void)
{
	long	i;

	xcmd((char *[]){"/usr/bin/clear", NULL});
	ft_prompt();
	ft_putstr_fd(g_sh->line, 0);
	i = ft_strlen(g_sh->line);
	while (i > g_sh->line_cursor)
	{
		ft_putstr_fd(g_sh->events->lf, 0);
		i--;
	}
	return (0);
}

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
			jump_sides((char []){27, 91, 70, 0});
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
