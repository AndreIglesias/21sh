/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:23:41 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/01 22:57:04 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sh_export(int argc, char **argv)
{
	char	*check;
	char	*tmp;
	char	*tmp2;

	if (argc > 1 && argv[1])
	{
		check = get_value(g_sh->ev, argv[1]);
		if (check)
			delete_value(&g_sh->ev, argv[1], ft_strlen(argv[1]), 0);
		tmp = ft_strjoin(argv[1], "=");
		tmp2 = ft_strjoin(tmp, argv[2]);
		free(tmp);
		insert_trie(&g_sh->ev, tmp2, ft_strlen(argv[1]));
		free(tmp2);
	}
	else
		sh_env();
	g_sh->last_status = 0;
}
