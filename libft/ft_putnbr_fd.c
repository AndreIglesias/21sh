/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:40:27 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/06 18:34:00 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putint(int nb, int fd)
{
	if (nb > 9)
		ft_putint(nb / 10, fd);
	ft_putchar_fd(nb % 10 + '0', fd);
}

static void	ft_putnint(unsigned int n, int fd)
{
	if (n > 9)
		ft_putnint(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		nb = -n;
		ft_putchar_fd('-', fd);
		ft_putnint(nb, fd);
	}
	else
		ft_putint(n, fd);
}
