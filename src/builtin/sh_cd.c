/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:04:58 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/24 23:49:25 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*get_home_dir(t_trie *ev, char *path)
{
	char	*tmp;

	tmp = get_value(ev, "HOME");
	if (tmp)
	{
		tmp = ft_strjoin(tmp, &path[1]);
		return (tmp);
	}
	return (NULL);
}

static void	update_ev(char *key, char *argv)
{
	char	*check;
	char	*tmp;
	char	*tmp2;

	check = get_value(g_sh->ev, key);
	if (check)
		delete_value(&g_sh->ev, key, ft_strlen(key), 0);
	tmp = ft_strjoin(argv, "=");
	tmp2 = ft_strjoin(tmp, argv);
	free(tmp);
	insert_trie(&g_sh->ev, tmp2, ft_strlen(key));
	free(tmp2);
}

int	sh_cd(int argv, char **argc)
{
	char	*tmp;

	if (argv == 2)
	{
		if (argc[1] && argc[1][0] == '~')
			tmp = get_home_dir(g_sh->ev, argc[1]);
		else
			tmp = ft_strdup(argc[1]);
		if (!chdir(tmp))
		{
			update_ev("PWD", tmp);
			free(tmp);
			return (EXIT_SUCCESS);
		}
		else
		{
			ft_putstr_fd(BOLD"minishell: cd: "BLUE, 2);
			ft_putstr_fd(argc[1], 2);
			ft_putstr_fd(E0M""BOLD" :no such file or directory\n"E0M, 2);
		}
		free(tmp);
	}
	return (EXIT_FAILURE);
}
