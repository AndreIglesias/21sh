/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:07:58 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/16 15:33:00 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	assignation(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	store_envar(t_shell *sh, char **ev)
{
	int	i;
	int	assign;

	i = 0;
	while (ev[i])
	{
		assign = assignation(ev[i]);
		insert_trie(&sh->ev, ev[i], assign);
		i++;
	}
}
