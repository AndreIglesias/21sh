/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:23:41 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/04 13:48:39 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	parse_env(int argc, char *argv)
{
	int	i;

	i = 0;
	if (ft_isdigit(argv[0]) || argv[0] == '=')
		return (0);
	while ((argv[i] != '=' && argc == 2) || (argv[i] && argc == 3))
	{
		if (!ft_isalpha(argv[i]) && !ft_isdigit(argv[i]) && argv[i] != '_')
			return (0);
		i++;
		if ((argv[i] == '=' && argc == 2) || (argv[i] == 0 && argc == 3))
			return (1);
	}
	return (0);
}

void	export_eq(int argc, char **argv)
{
	char	*check;
	char	*tmp;
	char	*tmp2;

	if (argc == 2)
	{
		tmp = ft_strndup(argv[1], ft_counttil(argv[1], '='));
		check = get_value(g_sh->ev, tmp);
		if (check)
			delete_value(&g_sh->ev, tmp, ft_strlen(tmp), 0);
		free(tmp);
		insert_trie(&g_sh->ev, argv[1], ft_counttil(argv[1], '='));
	}
	else
	{
		check = get_value(g_sh->ev, argv[1]);
		if (check)
			delete_value(&g_sh->ev, argv[1], ft_strlen(argv[1]), 0);
		tmp = ft_strjoin(argv[1], "=");
		tmp2 = ft_strjoin(tmp, argv[2]);
		free(tmp);
		insert_trie(&g_sh->ev, tmp2, ft_strlen(argv[1]));
		free(tmp2);
	}
}

void	sh_export(int argc, char **argv)
{
	if (argc == 1)
		sh_env();
	else if (argc == 3 || argc == 2)
	{
		if (parse_env(argc, argv[1]))
			export_eq(argc, argv);
		else
		{
			ft_putstr_fd(BOLD"minishell: export:", 2);
			ft_putstr_fd(BLUE" ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(E0M"", 2);
			ft_putstr_fd(BOLD": not a valid identifier\n"E0M, 2);
			g_sh->last_status = 1;
			return ;
		}
	}
	g_sh->last_status = 0;
}
