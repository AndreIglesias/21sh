/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:04:58 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/24 09:24:56 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*get_home_dir(t_trie *ev, char *path)
{
	char	*tmp;

	tmp = get_value(ev, "HOME");
	if (tmp)
	{
		tmp = ft_strjoin(tmp, &path[1]);
		return (tmp);
	}
	return (NULL);
}

int	sh_cd(t_trie *ev, char *path)
{
	char	*tmp;

	if (path && path[0] == '~')
		tmp = get_home_dir(ev, path);
	else
		tmp = ft_strdup(path);
	if (!chdir(tmp))
	{
		if (tmp)
			free(tmp);
		tmp = getcwd(NULL, 0);
		sh_export(ev, "PWD", tmp);
		free(tmp);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd(BOLD"minishell: cd: "BLUE, 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(E0M""BOLD" :no such file or directory\n"E0M, 2);
	}
	free(tmp);
	return (EXIT_FAILURE);
}
