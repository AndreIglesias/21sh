/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 22:43:29 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/19 23:25:28 by ciglesia         ###   ########.fr       */
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

void	sigtstp_shell(int sig)
{
	(void)sig;
}
