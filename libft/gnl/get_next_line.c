/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:43:51 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/19 14:25:50 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_fstrjoin(char *s1, char *s2)
{
	char	*str;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = ft_memalloc(len);
	if (!str)
		return (NULL);
	if (str)
	{
		str = ft_strcat(str, s1);
		str = ft_strcat(str, s2);
	}
	free(s1);
	return (str);
}

static char	*ft_fstrdup(const char *s1, char *pitcher)
{
	char	*str;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = s1[i];
		i--;
	}
	free(pitcher);
	return (str);
}

static char	*fill_pitcher(const int fd, char *pitcher)
{
	char	guacal[BUFFER_SIZE + 1];
	int		last;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, guacal, 0))
		return (0);
	if (pitcher == NULL)
		pitcher = ft_strdup("");
	while (!(ft_strchr(pitcher, '\n')))
	{
		last = read(fd, guacal, BUFFER_SIZE);
		if (last < 0)
			return (0);
		guacal[last] = '\0';
		pitcher = ft_fstrjoin(pitcher, guacal);
		if (!last || !pitcher[0])
			break ;
	}
	return (pitcher);
}

int	fill_line(int carret, char **pitcher, char *tmp, char **line)
{
	*line = ft_strndup(*pitcher, carret);
	if (!(*line))
		return (-1);
	(*pitcher) = ft_fstrdup(tmp + 1, (*pitcher));
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*pitcher;
	char		*tmp;

	if (!line)
		return (-1);
	pitcher = fill_pitcher(fd, pitcher);
	if (!pitcher)
		return (-1);
	tmp = ft_strchr(pitcher, '\n');
	if (tmp != 0)
		return (fill_line(tmp - pitcher, &pitcher, tmp, line));
	else
	{
		*line = ft_strdup(pitcher);
		if (!(*line))
			return (-1);
		free(pitcher);
		pitcher = NULL;
		if ((*line)[0] == '\0')
			return (0);
		return (1);
	}
}
