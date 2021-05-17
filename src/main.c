/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 21:30:25 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/17 21:30:36 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	ft_minishell(t_shell *sh)
{
    ssize_t ready;

	ready = 0;
    while (ready != -1)
	{
		ft_putstr(tgetstr("vi", NULL));
		write(1, "\n$ ", 2);
		ft_putstr(tgetstr("ve", NULL));
		ready = get_cmd(sh);
		free(sh->line);
	}
	if (sh->line)
		free(sh->line);
}

int	main(int ac, char **av, char **ev)
{
	t_shell	*sh;
	char	*home;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_shell);
	signal(SIGQUIT, sigquit_shell);
	sh = ft_shell();
	if (!sh)
		exit(EXIT_FAILURE);
	store_envar(sh, ev);
	home = get_value(sh->ev, "HOME");
	if (!home)
	{
		ft_puterror(MINERR"HOME environmental variable not set\n"E0M, (void*)1);
		//free everything
	}
	sh->history_path = ft_strjoin(home, "/.minishell_history");//alias history=cat..
	load_history(sh);
	ft_minishell(sh);
	return (EXIT_SUCCESS);
}
