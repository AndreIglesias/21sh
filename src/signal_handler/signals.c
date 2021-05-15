/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 22:43:29 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/15 20:57:11 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sigint_shell(int sig)
{
	(void)sig;
	ft_putstr("^C\n");
}

void	sigquit_shell(int sig)
{
	(void)sig;
}
