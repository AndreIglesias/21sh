/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:43:51 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/18 21:46:28 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strndup(const char *s, size_t size)
{
	size_t		i;
	char		*dup;

	i = 0;
	while (s[i])
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < size)
	{
		dup[i] = (char)s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

static char	*ft_fstrjoin(char *s1, char *s2)
{
	char	*str;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(str = ft_memalloc(len)))
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
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
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
		if ((last = read(fd, guacal, BUFFER_SIZE)) < 0)
			return (0);
		guacal[last] = '\0';
		pitcher = ft_fstrjoin(pitcher, guacal);
		if (!last || !pitcher[0])
			break ;
	}
	return (pitcher);
}

int			get_next_line(const int fd, char **line)
{
	static char	*pitcher;
	char		*tmp;
	int			carret;

	if (!line || !(pitcher = fill_pitcher(fd, pitcher)))
		return (-1);
	if ((tmp = ft_strchr(pitcher, '\n')) != 0)
	{
		carret = tmp - pitcher;
		if (!(*line = ft_strndup(pitcher, carret)))
			return (-1);
		pitcher = ft_fstrdup(tmp + 1, pitcher);
		return (1);
	}
	else
	{
		if (!(*line = ft_strdup(pitcher)))
			return (-1);
		free(pitcher);
		pitcher = NULL;
		return (*line[0] == '\0') ? 0 : 1;
	}
}
