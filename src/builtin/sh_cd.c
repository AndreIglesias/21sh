/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 13:15:41 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/24 13:52:09 by ciglesia         ###   ########.fr       */
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

static void	update_ev(char *key, char *argv, int f)
{
	char	*check;
	char	*tmp;
	char	*tmp2;

	check = get_value(g_sh->ev, key);
	if (check)
		delete_value(&g_sh->ev, key, ft_strlen(key), 0);
	tmp = ft_strjoin(key, "=");
	tmp2 = ft_strjoin(tmp, argv);
	insert_trie(&g_sh->ev, tmp2, ft_strlen(key));
	if (f)
		free(argv);
	free(tmp);
	free(tmp2);
}

static void	cd_alone(void)
{
	char	*tmp;

	tmp = get_value(g_sh->ev, "HOME");
	if (!chdir(tmp))
	{
		update_ev("OLDPWD", get_value(g_sh->ev, "PWD"), 0);
		update_ev("PWD", tmp, 0);
		g_sh->last_status = 0;
		return ;
	}
	g_sh->last_status = 1;
}

static void	cd_more(void)
{
	ft_putstr_fd(BOLD"minishell: cd: "BLUE"too many"COLOR_E0M"\
 arguments\n"E0M, 2);
	g_sh->last_status = 1;
}

void	sh_cd(int ac, char **av)
{
	char	*tmp;

	if (ac == 1)
		return (cd_alone());
	if (ac != 2)
		return (cd_more());
	if (av[1] && av[1][0] == '~')
		tmp = get_home_dir(g_sh->ev, av[1]);
	else if (av[1] && av[1][0] == '-' && !av[1][1])
		tmp = ft_strdup(get_value(g_sh->ev, "OLDPWD"));
	else
		tmp = ft_strdup(av[1]);
	if (!chdir(tmp))
	{
		update_ev("OLDPWD", get_value(g_sh->ev, "PWD"), 0);
		update_ev("PWD", getcwd(NULL, 0), 1);
		g_sh->last_status = 0;
		free(tmp);
		return ;
	}
	ft_putstr_fd(BOLD"minishell: cd: "BLUE, 2);
	ft_putstr_fd(av[1], 2);
	ft_putstr_fd(E0M""BOLD": no such file or directory\n"E0M, 2);
	g_sh->last_status = 1;
	free(tmp);
}
