/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 00:51:32 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/02 01:30:52 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	**str_to_arr(char *name, char *av)
{
	char	**argv;

	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(name);
	argv[1] = ft_strdup(av);
	argv[2] = NULL;
	return (argv);
}

void	sh_execv(char *name, char **av)
{
	char	str[200];
	char	**argv;

	save_envp(g_sh->ev, str, 0);
	if (!av)
	{
		argv = str_to_arr(name, NULL);
		execve(name, argv, g_sh->envp);
		ft_freesplit(argv);
	}
	else
		execve(name, av, g_sh->envp);
	if (g_sh->envp)
	{
		ft_freesplit(g_sh->envp);
		g_sh->envp = NULL;
	}
}
