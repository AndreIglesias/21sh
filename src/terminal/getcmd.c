/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:08:33 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/26 19:01:03 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	buf[4] up & dw have 3 chars + '\0'
**	buf[7] ctrl+lf & ctrl+rg have 6 chars + '\0'
**	up 27 91 65
**	dw 27 91 66
**	ctr + left: 27 91 49   59 53 67 | ^[[1;5D
**	ctr + left: 27 91 49   59 53 68 | ^[[1;5C
**	FIN 27 91 70
**	HOME 27 91 72
*/

void	input_handler(void)
{
	int		e;
	char	buf[7];
	ssize_t	len;

	while (!ft_strchr(buf, '\n'))
	{
		buf[0] = 0;
		len = read(STDIN_FILENO, buf, 6);
		buf[len] = 0;
		e = keys_event(buf);
		if (e)
			ft_putstr(buf);
		if (e == 1 && buf[0] != '\n')
		{
			g_sh->line = ft_strins(g_sh->line, buf, g_sh->line_cursor - 1);
			if (g_sh->line && g_sh->line_cursor < ft_strlen(g_sh->line))
			{
				ft_putstr_fd(g_sh->events->sc, 0);
				ft_putstr(&g_sh->line[g_sh->line_cursor]);
				ft_putstr_fd(g_sh->events->rc, 0);
			}
		}
	}
}

ssize_t	get_cmd(void)
{
	int	s;

	input_handler();
	if (g_sh->line)
	{
		s = 0;
		while (g_sh->line[s] && g_sh->line[s] == ' ')
			s++;

	}
	if (g_sh->line && (!g_sh->line[0] || !g_sh->line[s]))
	{
		free(g_sh->line);
		g_sh->line = NULL;
	}
	if (g_sh->line)
		save_cmdline(&g_sh->history, ft_strdup(g_sh->line));
	return (0);
}
