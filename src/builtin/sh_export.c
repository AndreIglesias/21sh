/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:23:41 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/20 18:32:09 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sh_export(t_trie *ev, char *key, char *value)
{
	char	*check;
	char	*tmp;
	char	*tmp2;

	if (key)
	{
		check = get_value(ev, key);
		if (check)
			delete_value(&ev, key, ft_strlen(key), 0);
		tmp = ft_strjoin(key, "=");
		tmp2 = ft_strjoin(tmp, value);
		free(tmp);
		insert_trie(&ev, tmp2, ft_strlen(key));
		free(tmp2);
	}
	else
		sh_env(ev);
}
