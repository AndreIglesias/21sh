/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:14:52 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/27 19:24:44 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	ll_to_uchar(char *value)
{
	t_uchar		a;
	long long	tmp;

	tmp = ft_atoll(value);
	if (!tmp)
	{
		ft_putstr_fd(BOLD"minishell: exit: ", 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd(": numeric argument required\n"E0M, 2);
	}
	a = (t_uchar)tmp;
	return ((int)a);
}

void	sh_exit(char *value)
{
	int	fd;

	fd = open(g_sh->history_path, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd != -1)
		put_history_fd(g_sh->history, fd);
	if (g_sh->history)
		free_history(g_sh->history);
	if (g_sh->history_path)
		free(g_sh->history_path);
	if (g_sh->history_path)
		free(g_sh->events);
	if (g_sh->ev)
		ft_freetrie(&g_sh->ev);
	if (g_sh)
		free(g_sh);
	if (fd == -1)
		ft_puterror(BOLD"minishell: ~/.minishell_history not generated\n"E0M, 0);
	if (value && value[0] != '0')
		exit(ll_to_uchar(value));
	exit(EXIT_SUCCESS);
}
