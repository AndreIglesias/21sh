/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:04:58 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/20 13:22:34 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	sh_cd(t_trie *ev, char *path)
{
	char	*tmp;

	if (!chdir(path))
	{
		tmp = getcwd(NULL, 0);
		sh_export(ev, "PWD", tmp);
		free(tmp);
		return (1);
	}
	else
	{
		ft_putstr_fd(BOLD"minishell: cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n"E0M, 2);
	}
	return (0);
}
