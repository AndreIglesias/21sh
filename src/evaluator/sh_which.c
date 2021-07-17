/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:02:34 by jiglesia          #+#    #+#             */
/*   Updated: 2021/07/17 17:56:37 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	is_builtin(char *name)
{
	int	i;

	i = 0;
	while (g_sh->builtins[i])
	{
		if (!ft_strcmp(name, g_sh->builtins[i++]))
			return (1);
	}
	return (0);
}

char	*check_bin_path(char *path, char *name)
{
	char		**split;
	int			i;
	struct stat	buf;

	if (!path)
		return (NULL);
	split = ft_split(path, ':');
	path = NULL;
	i = 0;
	while (split[i])
	{
		split[i] = ft_realloc(split[i], 1);
		split[i] = ft_strcat(split[i], "/");
		path = ft_strjoin(split[i++], name);
		if (stat(path, &buf) == 0 && !S_ISDIR(buf.st_mode))
		{
			ft_freesplit(split);
			return (path);
		}
		free(path);
		path = NULL;
	}
	ft_freesplit(split);
	return (NULL);
}

char	*sh_which(char *name, t_trie *ev)
{
	char		*path;
	struct stat	buf;

	if (!name || !name[0])
		return (NULL);
	path = NULL;
	if (ft_strchr(name, '/'))
	{
		if (stat(name, &buf) == 0 && !S_ISDIR(buf.st_mode))
			return (ft_strdup(name));
	}
	else
		path = check_bin_path(get_value(ev, "PATH"), name);
	return (path);
}
