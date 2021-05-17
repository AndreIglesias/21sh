/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:30:05 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/17 20:52:57 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_history	*init_history(void)
{
	t_history	tmp;

	tmp = (t_history *)malloc(sizeof(t_history));
	if (!tmp)
		return (NULL);
	tmp->cmd = NULL;
	tmp->writen = 0;
	tmp->back = NULL;
	tmp->next = NULL;
	return (tmp);
}

void	fill_history(int fd, t_history *hst)
{
	char	*line;
	int		i;

	i = HRY_SIZE;
	line = NULL;
	while (get_next_line(fd, &line) && i--)
	{
		hst->cmd = line;
		line = NULL;
		hst->writen = 1;
		hst->back = init_history();
		hst->back->next = hst;
		hst = hst->back;
	}
	if (line)
		free(line);
	get_next_line(-1, &line);
	close(fd);
}

void	load_history(t_shell *sh)
{
	int	fd;

	fd = open(sh->history_path, O_RONLY);
	sh->history = init_history();
	if (fd > 0)
		fill_history(fd, sh->history);
}
