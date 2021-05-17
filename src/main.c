/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:46:45 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/17 21:09:48 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	ft_minishell(t_shell *sh)
{
    ssize_t ready;
	char	buf[4];

	ready = 0;
    while (ready != -1)
	{
		ft_putstr(tgetstr("vi", NULL));
		write(1, "\n$ ", 2);
		ft_putstr(tgetstr("ve", NULL));
		//getcmd(sh);
		ready = read(STDIN_FILENO, buf, 1);
		ft_putnbr(buf[0]);
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
