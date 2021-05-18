/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:54:43 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/18 14:17:58 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	ascii
**	4 = EOT
**	127 = DEL
*/

void	keys_event(char *buf, t_shell *sh)
{
	if (buf[0] == 4)
		exit(0);
	if (buf[0] == 127)
	{
		ft_putstr_fd(sh->events->lf, 0);
		ft_putstr_fd(sh->events->sc, 0);
		ft_putstr_fd(sh->events->ce, 0);
	}
}
