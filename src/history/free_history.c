/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 20:38:23 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/18 20:39:16 by jiglesia         ###   ########.fr       */
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
