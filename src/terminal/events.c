/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <ciglesia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 19:35:23 by user              #+#    #+#             */
/*   Updated: 2021/06/03 19:41:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	next_space(char *str, int i)
{
	int	my_space;

	if (str && str[i - 1])
	{
		my_space = 0;
		i--;
		if (str[i] == ' ')
			my_space = 1;
		while (i && (str[i] != ' ' || my_space))
		{
			if (str[i] != ' ')
				my_space = 0;
			i--;
		}
		if (!my_space && str[i] == ' ')
			i++;
	}
	return (i);
}

static int	next_char(char *str, int i)
{
	int	my_char;

	if (str && str[i])
	{
		my_char = 0;
		i++;
		if (str[i] != ' ')
			my_char = 1;
		while (str[i] && (str[i] == ' ' || my_char))
		{
			if (str[i] == ' ')
				my_char = 0;
			i++;
		}
	}
	return (i);
}

int	move_ctrl(char *buf, char *cl, char *cr)
{
	size_t	x;

	if (!ft_strcmp(cl, buf) && g_sh->line_cursor)
	{
		x = next_space(g_sh->line, g_sh->line_cursor);
		while (x < g_sh->line_cursor)
		{
			ft_putstr_fd(g_sh->events->lf, 0);
			g_sh->line_cursor--;
		}
	}
	else if (!ft_strcmp(cr, buf) && g_sh->line_cursor
		< ft_strlen(g_sh->line))
	{
		x = next_char(g_sh->line, g_sh->line_cursor);
		while (g_sh->line_cursor < x)
		{
			ft_putstr_fd(g_sh->events->rg, 0);
			g_sh->line_cursor++;
		}
	}
	return (0);
}

int	jump_sides(char *buf)
{
	if (buf[2] == 70 && g_sh->line_cursor < ft_strlen(g_sh->line))
	{
		while (g_sh->line_cursor < ft_strlen(g_sh->line))
		{
			ft_putstr_fd(g_sh->events->rg, 0);
			g_sh->line_cursor++;
		}
	}
	if (buf[2] == 72 && g_sh->line_cursor)
	{
		while (g_sh->line_cursor)
		{
			ft_putstr_fd(g_sh->events->lf, 0);
			g_sh->line_cursor--;
		}
	}
	return (0);
}

int	ctrl_l(void)
{
	char	**argv;
	int		pid;
	size_t	i;

	pid = fork();
	if (pid)
		parent_fork(pid);
	else
	{
		argv = str_to_arr("/usr/bin/clear", NULL);
		sh_execv(argv[0], argv);
		ft_freesplit(argv);
		sh_exit(NULL);
	}
	ft_prompt();
	ft_putstr(g_sh->line);
	i = ft_strlen(g_sh->line);
	while (i > g_sh->line_cursor)
	{
		ft_putstr_fd(g_sh->events->lf, 0);
		i--;
	}
	return (0);
}
