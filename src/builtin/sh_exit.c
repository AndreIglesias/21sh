/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:14:52 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/20 17:53:55 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sh_exit(void)
{
	free_history(g_sh->history);
	free(g_sh->history_path);
	free(g_sh->events);
	exit(EXIT_SUCCESS);
}
