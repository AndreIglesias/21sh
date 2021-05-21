/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 22:43:29 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/20 18:48:46 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sigint_shell(int sig)
{
	(void)sig;
	ft_putstr("^C\n");
	free(g_sh->line);
	g_sh->line = NULL;
	g_sh->history_cursor = g_sh->history;
	g_sh->line = NULL;
	g_sh->line_tmp = NULL;
	g_sh->line_cursor = 0;
	ft_putstr(tgetstr("vi", NULL));
	ft_prompt();
	ft_putstr(tgetstr("ve", NULL));
}

void	sigquit_shell(int sig)
{
	(void)sig;
}

void	sigtstp_shell(int sig)
{
	(void)sig;
}
