/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:54:43 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/03 01:18:51 by ciglesia         ###   ########.fr       */
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

static char	g_del[] = {27, 91, 51, 126, 0};
static char	g_cu[] = {27, 91, 49, 59, 53, 65, 0};
static char	g_cd[] = {27, 91, 49, 59, 53, 66, 0};
static char	g_cr[] = {27, 91, 49, 59, 53, 67, 0};
static char	g_cl[] = {27, 91, 49, 59, 53, 68, 0};
static char	g_home[] = {27, 91, 72, 0};
static char	g_end[] = {27, 91, 70, 0};

int	move_cursor(char *buf)
{
	if (ft_strlen(buf) == 6)
	{
		if (!ft_strcmp(g_cu, buf) || !ft_strcmp(g_cd, buf)
			||!ft_strcmp(g_cl, buf) || !ft_strcmp(g_cr, buf))
			return (move_ctrl(buf));
	}
	else if (ft_strlen(buf) == 3)
	{
		if (!ft_strcmp(g_home, buf) || !ft_strcmp(g_end, buf))
			return (jump_sides(buf));
		else if (!ft_strcmp(g_sh->events->rg, buf) && g_sh->shadow)
			return (insert_shadow());
		else if (!ft_strcmp(g_sh->events->lf, buf)
			|| !ft_strcmp(g_sh->events->rg, buf))
			return (move_arrows(buf));
	}
	else if (g_sh->line && g_sh->line[0])
	{
		if (g_sh->line_cursor > 0 && buf[0] == 127)
			return (delete_key());
		else if (g_sh->line_cursor < g_sh->line_size && !ft_strcmp(g_del, buf))
			return (revdel_key());
	}
	return (42);
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
	g_sh->line_size = ft_strlen(g_sh->line);
	mcursor = move_cursor(buf);
	if (mcursor != 42)
		return (mcursor);
	if (!ft_strcmp(g_sh->events->up, buf) || !ft_strcmp(g_sh->events->dw, buf))
		return (browse_history(buf));
	if (ft_strlen(buf) == 1)
	{
		if (buf[0] == 12)
			return (ctrl_l());
		if (buf[0] == 9)
			return (auto_complete());
		if (buf[0] == 1)
			return (ft_select());
	}
	return (check_buffer(buf));
}
