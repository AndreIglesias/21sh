/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 01:46:33 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/06 19:54:52 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putint(int nb)
{
	if (nb > 9)
		ft_putint(nb / 10);
	ft_putchar(nb % 10 + '0');
}

static void	ft_putnint(unsigned int n)
{
	if (n > 9)
		ft_putnint(n / 10);
	ft_putchar(n % 10 + '0');
}

void	ft_putnbr(int n)
{
	unsigned int	nb;

	if (n < 0)
	{
		nb = -n;
		ft_putchar('-');
		ft_putnint(nb);
	}
	else
		ft_putint(n);
}
