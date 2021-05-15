/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:46:45 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/15 21:13:37 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	main(int ac, char **av, char **ev)
{
	t_shell	*sh;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_shell);
	signal(SIGQUIT, sigquit_shell);
	sh = ft_shell();
	if (!sh)
		exit(EXIT_FAILURE);
	store_envar(sh, ev);
	return (EXIT_SUCCESS);
}
