/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:43:51 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/08 23:06:08 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	fill_bowl(char **bowl, char *spoon)
{
	char	*dup;
	int		i;
	int		j;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(*bowl) + BUFFER_SIZE + 1));
	if (!dup)
		return ;
	i = 0;
	while (*bowl && (*bowl)[i])
	{
		dup[i] = (*bowl)[i];
		i++;
	}
	if (bowl)
		free(*bowl);
	(*bowl) = dup;
	j = 0;
	while (spoon[j])
	{
		(*bowl)[i + j] = spoon[j];
		j++;
	}
}

void	scrap_bowl(char **bowl, int i)
{
	char *dup;

	if ((*bowl)[i])
	{
		dup = ft_strdup(&(*bowl)[i]);
		free(*bowl);
		(*bowl) = dup;
	}
	else
	{
		free(*bowl);
		(*bowl) = NULL;
	}
}

int	fill_line(char **bowl, char **line)
{
	int	i;

	i = 0;
	(*line) = (char *)malloc(sizeof(char) * (ft_strlen(*bowl) + 1));
	if (!(*line))
		return (-1);
	(*line)[i] = 0;
	while ((*bowl)[i] && (*bowl)[i] != '\n')
	{
		(*line)[i] = (*bowl)[i];
		(*line)[++i] = 0;
	}
	write(1, "hi\n", 3);
	if ((*bowl)[i])
	{
		scrap_bowl(bowl, i + 1);
		return (1);
	}
	else
	{
		if (*bowl)
			free(*bowl);
		(*bowl) = NULL;
		return (0);
	}
}

int	get_next_line(int fd, char **line)
{
	char			spoon[BUFFER_SIZE + 1];
	static char		*bowl = NULL;
	size_t			j;

	if (fd >= 0 && line && !(read(fd, spoon, 0)))
	{
		j = read(fd, spoon, BUFFER_SIZE);
		while (j > 0)
		{
			spoon[j] = 0;
			fill_bowl(&bowl, spoon);
			j = read(fd, spoon, BUFFER_SIZE);
		}
		return (fill_line(&bowl, line));
	}
	return (-1);
}
