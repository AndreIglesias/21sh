/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:08:33 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/18 14:18:08 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	input_handler(t_shell *sh)
{
	char	buf[2];
	ssize_t	len;

	buf[0] = 0;
	(void)sh;
	while (!ft_strchr(buf, '\n'))
	{
		len = read(STDIN_FILENO, buf, 1);
		buf[len] = 0;
		keys_event(buf, sh);
		ft_putstr(buf);
		//ft_putnbr(buf[0]);
	}
}

ssize_t	get_cmd(t_shell *sh)
{
	input_handler(sh);
	return (0);
}
