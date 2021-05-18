/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:54:43 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/18 21:35:42 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	ascii
**	4 = EOT
**	127 = DEL
*/

int		keys_event(char *buf, t_shell *sh)
{
	if (buf[0] == 4)
		exit(0);
	if (buf[0] == 127 && sh->line && sh->line[0])
	{
		ft_putstr_fd(sh->events->lf, 0);
		ft_putstr_fd(sh->events->sc, 0);
		ft_putstr_fd(sh->events->ce, 0);
		sh->line[ft_strlen(sh->line) - 1] = 0;
		return (2);
	}
	if (!ft_strcmp(sh->events->up, buf) || !ft_strcmp(sh->events->dw, buf))
		return (0);
	return (1);
}
