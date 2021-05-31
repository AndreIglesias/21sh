/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:30:05 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/25 00:29:29 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static t_history	*init_history(void)
{
	t_history	*tmp;

	tmp = malloc(sizeof(t_history));
	if (!tmp)
		return (NULL);
	tmp->cmd = NULL;
	tmp->writen = 0;
	tmp->back = NULL;
	tmp->next = NULL;
	return (tmp);
}

void	save_cmdline(t_history **hst, char *line)
{
	t_history	*tmp;

	tmp = init_history();
	tmp->cmd = line;
	tmp->next = (*hst);
	if (*hst)
		(*hst)->back = tmp;
	(*hst) = tmp;
}

static void	fill_history(int fd, t_history **hst)
{
	char	*line;
	int		i;

	i = HRY_SIZE;
	line = NULL;
	while (get_next_line(fd, &line) > 0 && i--)
	{
		save_cmdline(hst, line);
		line = NULL;
	}
	get_next_line(-1, &line);
	if (line)
		free(line);
	close(fd);
}

void	load_history(void)
{
	int	fd;

	fd = open(g_sh->history_path, O_RDONLY);
	if (fd > 0)
		fill_history(fd, &g_sh->history);
}

void	put_history_fd(t_history *hst, int fd)
{
	size_t		size;
	t_history	*tmp;

	tmp = hst;
	size = HRY_SIZE;
	while (--size && tmp && tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		ft_putstr_fd(tmp->cmd, fd);
		ft_putchar_fd('\n', fd);
		tmp = tmp->back;
	}
}
