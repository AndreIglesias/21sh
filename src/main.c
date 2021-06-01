/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 21:36:00 by ciglesia          #+#    #+#             */
/*   Updated: 2021/06/01 12:24:19 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_shell	*g_sh;

void	ft_minishell(void)
{
	ssize_t	ready;

	ready = 1;
	while (ready > 0)
	{
		g_sh->history_cursor = g_sh->history;
		g_sh->line = NULL;
		g_sh->line_tmp = NULL;
		g_sh->line_cursor = 0;
		ft_putstr(tgetstr("vi", NULL));
		ft_prompt();
		ft_putstr(tgetstr("ve", NULL));
		ready = get_cmd();
		ft_putstr(tgetstr("vi", NULL));
		if (g_sh->line)
		{
			if (ft_analyze() != EXIT_SUCCESS)
				g_sh->last_status = 2;
			ft_evaluate();
			free_ast();
		}
		free(g_sh->line);
		if (g_sh->line_tmp)
			free(g_sh->line_tmp);
	}
}

int	main(int ac, char **av, char **ev)
{
	char	*home;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_shell);
	signal(SIGQUIT, sigquit_shell);
	signal(SIGTSTP, sigtstp_shell);
	g_sh = ft_shell();
	if (!g_sh)
		exit(EXIT_FAILURE);
	store_envar(ev);
	home = get_value(g_sh->ev, "HOME");
	if (!home)
	{
		ft_puterror(MINERR"HOME environmental variable not set\n"E0M, (void *)1);
		sh_exit(NULL);
	}
	g_sh->history_path = ft_strjoin(home, "/.minishell_history");
	load_history();
	ft_minishell();
	sh_exit("2");
	return (EXIT_SUCCESS);
}
