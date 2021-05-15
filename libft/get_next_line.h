/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:20:59 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/08 14:30:54 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include "libft.h"

int		get_next_line(int fd, char **line);
size_t	ft_strlen(const char *s);
char	*ft_realloc(char *bowl);
char	*ft_strchr(const char *s, int c);

#endif
