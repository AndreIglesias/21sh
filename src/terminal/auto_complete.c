/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 21:02:45 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/17 21:27:51 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	complete_builtin(char *name, size_t size)
{
	int		i;
	char	*str;

	i = 0;
	while (g_sh->builtins[i])
	{
		str = g_sh->builtins[i];
		if (!ft_strncmp(str, name, size))
		{
			g_sh->line = ft_strins(g_sh->line, &str[size], g_sh->line_cursor);
			ft_putstr_fd(&str[size], 0);
			ft_putstr_fd(g_sh->events->sc, 0);
			ft_putstr_fd(&g_sh->line[ft_strlen(&str[size]) + g_sh->line_cursor],
				0);
			ft_putstr_fd(g_sh->events->rc, 0);
			g_sh->line_cursor += (ft_strlen(str) - size);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	complete_search(char *name)
{
	char	*path;
	int		lslash;
	DIR		*dir;

	if (!name || !name[0])
		return ;
	if (ft_strchr(name, '/'))
	{
		lslash = last_slash(name);
		if (!lslash)
			return ;
		path = ft_strndup(name, lslash);
		dir = opendir(path);
		if (dir)
			complete_in_dir(path, &name[lslash + 1], dir,
				ft_strlen(&name[lslash + 1]));
		free(path);
	}
	else if (!complete_builtin(name, ft_strlen(name)))
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
		if (i)
			i++;
		str = ft_strndup(&g_sh->line[i], g_sh->line_cursor - i);
		complete_search(str);
		free(str);
	}
	return (0);
}
