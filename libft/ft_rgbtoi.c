/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgbtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 19:03:30 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/06 19:56:18 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_rgbtoi(unsigned char r, unsigned char g, unsigned char b)
{
	int	red;
	int	green;
	int	blue;

	red = (0xfeff01 + r) * (r != 0);
	green = (0xfe01 + g) * (g != 0);
	blue = b;
	return (red + green + blue);
}
