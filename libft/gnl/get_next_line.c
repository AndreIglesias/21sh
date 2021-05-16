/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:43:51 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/16 16:12:04 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_bowl(char *bowl, char *spoon)
{
	char	*dup;
	int		i;
	int		j;

	i = 0;
	dup = bowl;
	bowl = (char *)malloc(ft_strlen(dup) + BUFFER_SIZE + 1);
	if (!bowl)
		return (ft_strdup(""));
	while (dup && dup[i])
	{
		bowl[i] = dup[i];
		i++;
	}
	bowl[i] = 0;
	if (dup)
		free(dup);
	j = 0;
	while (spoon[j])
	{
		bowl[i + j] = spoon[j];
		j++;
	}
	return (bowl);
}

int	check_jump(char *bowl)
{
	int	i;

	i = 0;
	while (bowl[i])
		if (bowl[i++] == '\n')
			return (0);
	return (1);
}

void	scrap_bowl(char **bowl, int i)
{
	char *dup;

	if ((*bowl)[i] && (*bowl)[i + 1])
	{
		dup = ft_strdup(&(*bowl)[i + 1]);
		free(*bowl);
		(*bowl) = dup;
	}
	else
	{
		free(*bowl);
		(*bowl) = ft_strdup("");
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
	while (*bowl && (*bowl)[i] && (*bowl)[i] != '\n')
	{
		(*line)[i] = (*bowl)[i];
		(*line)[++i] = 0;
	}
	if (*bowl && (*bowl)[i])
	{
		scrap_bowl(bowl, i);
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

	if (!bowl)
		bowl = ft_strdup("");
	if (fd >= 0 && line && !(read(fd, spoon, 0)))
	{
		j = read(fd, spoon, BUFFER_SIZE);
		while (j > 0)
		{
			spoon[j] = 0;
			bowl = fill_bowl(bowl, spoon);
			if (!check_jump(bowl))
				break ;
			j = read(fd, spoon, BUFFER_SIZE);
		}
		return (fill_line(&bowl, line));
	}
	return (-1);
}
