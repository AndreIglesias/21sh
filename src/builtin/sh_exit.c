/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:14:52 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/20 18:45:42 by ciglesia         ###   ########.fr       */
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
	if (g_sh)
		free(g_sh);
	exit(EXIT_SUCCESS);
}
