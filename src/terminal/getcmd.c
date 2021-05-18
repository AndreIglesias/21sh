/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:08:33 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/18 21:42:14 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	buf[4] up & dw have 3 chars + '\0'
**	up 27 91 65
**	dw 27 91 66
*/

void	input_handler(t_shell *sh)
{
	int		e;
	char	buf[4];
	ssize_t	len;

	buf[0] = 0;
	while (!ft_strchr(buf, '\n'))
	{
		len = read(STDIN_FILENO, buf, 3);
		buf[len] = 0;
		e = keys_event(buf, sh);
		if (e)
			ft_putstr(buf);
		if (e == 1 && buf[0] != '\n')
			sh->line = ft_strjoin(sh->line, buf);
		/*
		ft_putstr("[");
		ft_putstr(sh->line);
		ft_putstr("] len: ");
		ft_putnbr(ft_strlen(sh->line));
		ft_putstr("\n");
		*/
	}
	printf("line: [%s] len: %zu\n", sh->line, ft_strlen(sh->line));
}

ssize_t	get_cmd(t_shell *sh)
{
	input_handler(sh);
	return (0);
}
