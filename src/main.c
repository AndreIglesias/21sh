/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 21:36:00 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/03 01:13:24 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_shell	*g_sh;

void	init_line(void)
{
	g_sh->line = NULL;
	g_sh->line_size = 0;
	g_sh->line_tmp = NULL;
	g_sh->shadow = NULL;
	g_sh->line_cursor = 0;
	g_sh->prompt_x = PROMPT_LEN;
	g_sh->prompt_y = 0;
	g_sh->select_start = -1;
	g_sh->select_end = -1;
}

void	ft_minishell(ssize_t ready)
{
	while (ready > 0)
	{
		g_sh->history_cursor = g_sh->history;
		init_line();
		ft_putstr_fd(tgetstr("vi", NULL), 0);
		ft_prompt();
		ft_putstr_fd(tgetstr("ve", NULL), 0);
		ready = get_cmd();
		if (g_sh->line)
		{
			if (ft_analyze() != EXIT_SUCCESS)
				g_sh->last_status = 2;
			if (EVAL)
				ft_evaluate();
			free_ast();
		}
		free(g_sh->line);
		if (g_sh->line_tmp)
			free(g_sh->line_tmp);
	}
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)),
	char **ev)
{
	char		*home;
	static char	*builtins[] = {"echo", "cd", "pwd", "export", "setenv",
							"unset", "unsetenv",	"env", "exit",
							"history", "syntax", NULL};

	signal(SIGINT, sigint_shell);
	signal(SIGQUIT, sigquit_shell);
	signal(SIGTSTP, sigtstp_shell);
	g_sh = ft_shell();
	g_sh->builtins = builtins;
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
	ft_minishell(1);
	sh_exit("2");
	return (EXIT_SUCCESS);
}
