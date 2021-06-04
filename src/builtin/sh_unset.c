/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 23:46:17 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/04 15:23:09 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	valid_env(char *argv)
{
	int	i;

	i = 0;
	if (ft_isdigit(argv[0]) || argv[0] == '=')
		return (0);
	while (argv[i])
	{
		if (!ft_isalpha(argv[i]) && !ft_isdigit(argv[i]) && argv[i] != '_')
			return (0);
		i++;
		if (argv[i] == 0)
			return (1);
	}
	return (0);
}

void	sh_unset(int argc, char **key)
{
	int		i;

	if (argc > 1)
	{
		i = 0;
		g_sh->last_status = 0;
		while (key[++i])
		{
			if (valid_env(key[i]))
				delete_value(&g_sh->ev, key[1], ft_strlen(key[1]), 0);
			else
			{
				ft_putstr_fd(BOLD"minishell: unset: ", 2);
				ft_putstr_fd(BLUE"", 2);
				ft_putstr_fd(key[i], 2);
				ft_putstr_fd(""E0M, 2);
				ft_putstr_fd(BOLD": not a valid identifier\n"E0M, 2);
				g_sh->last_status = 1;
			}
		}
	}
	else
		g_sh->last_status = 0;
}
