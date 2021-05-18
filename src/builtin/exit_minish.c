/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:09:16 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/18 20:29:21 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	free_history(t_history *hst)
{
	while (hst)
	{
		if (!hst->next)
		{
			free(hst->cmd);
			free(hst);
			hst = NULL;
			break ;
		}
		hst = hst->next;
		free(hst->back->cmd);
		free(hst->back);
		hst->back = NULL;
	}
}

void	exit_minish(t_shell *sh)
{
	free_history(sh->history);
	free(sh->history_path);
	free(sh->events);
	exit(EXIT_SUCCESS);
}
