/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:46:45 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/16 15:49:52 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	ft_minishell(t_shell *sh)
{
    size_t len;
    ssize_t read;

	len = 0;
	read = 0;
    while (read != -1)
	{
		write(1, "$ ", 2);
		read = getline(&sh->line, &len, stdin);
		sh->line[ft_strlen(sh->line) - 1] = 0;
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
	sh->history = ft_strjoin(home, "/.minishell_history");//alias history=cat..
	//load history
	ft_minishell(sh);
	return (EXIT_SUCCESS);
}
