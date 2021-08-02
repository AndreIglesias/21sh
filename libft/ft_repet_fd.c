/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repet_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:12:42 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/25 17:13:31 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_repet_fd(char c, int i, const int fd)
{
	int nb;

	nb = 0;
	while (nb < i)
		nb += write(fd, &c, 1);
	return (nb);
}
