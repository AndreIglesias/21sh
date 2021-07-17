/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 19:10:49 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/17 19:14:29 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	exec_perm(char *folder, char *name)
{
	char		*path;
	struct stat	buf;

	path = ft_calloc(2 + ft_strlen(name) + ft_strlen(folder), sizeof(char));
	ft_strcat(path, folder);
	ft_strcat(path, "/");
	ft_strcat(path, name);
	if (stat(path, &buf) == 0 && buf.st_mode & S_IXUSR && !S_ISDIR(buf.st_mode))
	{
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	complete_in_dir(char *folder, char *name, DIR *dir, size_t size)
{
	struct dirent	*dp;
	char			str[256];

	dp = readdir(dir);
	while (dp)
	{
		ft_bzero(str, sizeof(str));
		ft_strcat(str, dp->d_name);
		if (!ft_strncmp(str, name, size) && exec_perm(folder, str))
		{
			g_sh->line = ft_strins(g_sh->line, &str[size], g_sh->line_cursor);
			ft_putstr_fd(&str[size], 0);
			ft_putstr_fd(g_sh->events->sc, 0);
			ft_putstr_fd(&g_sh->line[ft_strlen(&str[size]) + g_sh->line_cursor],
				0);
			ft_putstr_fd(g_sh->events->rc, 0);
			g_sh->line_cursor += (ft_strlen(str) - size);
			closedir(dir);
			return (1);
		}
		dp = readdir(dir);
	}
	closedir(dir);
	return (0);
}

void	path_completion(char *path, char *name)
{
	char	**split;
	int		i;
	DIR		*dir;

	if (!path)
		return ;
	split = ft_split(path, ':');
	i = 0;
	while (split[i])
	{
		dir = opendir(split[i]);
		if (dir && complete_in_dir(split[i], name, dir, ft_strlen(name)))
		{
			ft_freesplit(split);
			return ;
		}
		i++;
	}
	ft_freesplit(split);
}
