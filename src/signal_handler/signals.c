/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 22:43:29 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/23 20:22:23 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sig_child(int sig)
{
	t_ast	*tmp;

	tmp = g_sh->pid;
	if (sig == SIGQUIT || sig == SIGINT)
	{
		while (tmp->next)
			tmp = tmp->next;
		kill(tmp->ac, sig);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 1);
		else
			ft_putstr_fd("\n", 1);
	}
}

void	sigint_shell(int sig)
{
	(void)sig;
	ft_putstr("^C\n");
	free(g_sh->line);
	g_sh->history_cursor = g_sh->history;
	if (g_sh->line_tmp)
		free(g_sh->line_tmp);
	init_line();
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
