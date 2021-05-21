/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:14:52 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/21 16:17:58 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sh_exit(void)
{
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
	exit(EXIT_SUCCESS);
}
