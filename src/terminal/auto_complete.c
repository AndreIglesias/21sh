/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 21:02:45 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/17 01:54:56 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	last_slash(char *str)
{
	int	i;
	int	slash;

	i = 0;
	slash = 0;
	while (str[i])
	{
		if (str[i] == '/')
			slash = i;
		i++;
	}
	return (slash);
}

int	exec_perm(char *folder, char *name)
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

int	complete_in_dir(char *folder, char *name)
{
	DIR				*dir;
	struct dirent	*dp;
	char			str[256];
	size_t			size;

	dir = opendir(folder);
	if (!dir)
		return (0);
	size = ft_strlen(name);
	dp = readdir(dir);
	while (dp)
	{
		ft_bzero(str, sizeof(str));
		ft_strcat(str, dp->d_name);
		if (!ft_strncmp(str, name, size) && exec_perm(folder, str))
		{
			g_sh->line = ft_strins(g_sh->line, &str[size], g_sh->line_cursor);
			ft_putstr_fd(&g_sh->line[g_sh->line_cursor], 0);
			g_sh->line_cursor += (ft_strlen(str) - size);
			//ft_putchar('\n');ft_putstr(name);
			return (1);
		}
		dp = readdir(dir);
	}
	closedir(dir);
	return (0);
}

void	path_completion(char *path, char *name)
{
	char		**split;
	int			i;

	if (!path)
		return ;
	split = ft_split(path, ':');
	i = 0;
	while (split[i])
	{
		if (complete_in_dir(split[i], name))
		{
			ft_freesplit(split);
			return ;
		}
		i++;
	}
	ft_freesplit(split);
}

void	complete_search(char *name)
{
	char	*path;
	int		lslash;

	if (!name || !name[0])
		return ;
	if (ft_strchr(name, '/'))
	{
		lslash = last_slash(name);
		if (!lslash)
			return ;
		path = ft_strndup(name, lslash);
		complete_in_dir(path, &name[lslash + 1]);
		free(path);
	}
	else
		path_completion(get_value(g_sh->ev, "PATH"), name);
}

int	auto_complete(void)
{
	int		i;
	char	*str;

	if ((long)g_sh->line_cursor - 1 >= 0
		&& 32 < g_sh->line[g_sh->line_cursor - 1]
		&& g_sh->line[g_sh->line_cursor - 1] < 127)
	{
		i = g_sh->line_cursor - 1;
		while (i && 32 < g_sh->line[i] && g_sh->line[i] < 127)
			i--;
		str = ft_strndup(&g_sh->line[i], g_sh->line_cursor - i);
		complete_search(str);
	}
	return (0);
}
