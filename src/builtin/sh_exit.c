/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:14:52 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/20 19:39:07 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sh_exit(void)
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
	exit(EXIT_SUCCESS);
}
