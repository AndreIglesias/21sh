/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:16:09 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/24 23:51:06 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sh_history(void)
{
	size_t		size;
	t_history	*tmp;
	size_t		i;

	tmp = g_sh->history;
	size = HRY_SIZE;
	while (--size && tmp && tmp->next)
		tmp = tmp->next;
	i = 1;
	while (tmp)
	{
		ft_putstr("   ");
		ft_putnbr(i++);
		ft_putstr("  ");
		ft_putstr_fd(tmp->cmd, 1);
		ft_putchar_fd('\n', 1);
		tmp = tmp->back;
	}
}
