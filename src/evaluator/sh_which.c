/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:02:34 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/20 12:05:48 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	is_builtin(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (1);
	if (!ft_strcmp(name, "cd"))
		return (1);
	if (!ft_strcmp(name, "pwd"))
		return (1);
	if (!ft_strcmp(name, "export"))
		return (1);
	if (!ft_strcmp(name, "unset"))
		return (1);
	if (!ft_strcmp(name, "env"))
		return (1);
	if (!ft_strcmp(name, "exit"))
		return (1);
	return (0);
}

char	*sh_which(char *name, t_trie *ev)
{
	char	*path;
	char	**split;
	int		i;
	t_stat	buf;

	path = get_value(ev, "PATH");
	split = ft_split(path, ':');
	path = NULL;
	i = 0;
	while (split[i])
	{
		split[i] = ft_realloc(split[i], 1);
		split[i] = ft_strcat(split[i], "/");
		path = ft_strjoin(split[i], name);
		if (stat(path, &buf) == 0)
		{
			ft_freesplit(split);
			return (path);
		}
		free(path);
		path = NULL;
		i++;
	}
	ft_freesplit(split);
	return (NULL);
}
