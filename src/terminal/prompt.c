/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 19:17:09 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/23 18:45:47 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	print_pwd(char *pwd)
{
	char	*home;

	home = get_value(g_sh->ev, "HOME");
	ft_putstr(BOLD""GRAY);
	ft_putstr(BG_CYAN);
	if (home && !ft_strncmp(home, pwd, ft_strlen(home)))
	{
		ft_putstr(" ~");
		ft_putstr(&pwd[ft_strlen(home)]);
	}
	else
		ft_putstr(pwd);
	ft_putstr(" ");
	ft_putstr(BG_E0M""CYAN);
	ft_putstr(ARROW);
	ft_putstr(E0M);
}

static void	prompt_status(char *user)
{
	static char	success[] = {0xe2, 0x9c, 0x94, 0x00};
	static char	fail[] = {0xe2, 0x9c, 0x98, 0x00};

	ft_putstr(BG_LIGHT_GRAY" ");
	if (g_sh->last_status == EXIT_SUCCESS)
		ft_putstr(success);
	else
	{
		ft_putstr(BLACK);
		ft_putstr(fail);
	}
	if (user)
		ft_putstr(" "BG_GRAY""LIGHT_GRAY);
	else
		ft_putstr(" "BG_CYAN""LIGHT_GRAY);
	ft_putstr(ARROW);
}

void	ft_prompt(void)
{
	char		*user;
	char		*pwd;

	ft_putstr("╭─");
	user = get_value(g_sh->ev, "USER");
	pwd = getcwd(NULL, 0);
	prompt_status(user);
	if (user)
	{
		ft_putstr(GREEN""BG_GRAY" ");
		ft_putstr(user);
		ft_putstr(" "E0M);
	}
	if (user && pwd)
	{
		ft_putstr(BG_CYAN""GRAY);
		ft_putstr(ARROW);
	}
	if (pwd)
	{
		print_pwd(pwd);
		free(pwd);
	}
	ft_putstr(" ❱\n");
	ft_putstr("╰◠◡ ");
}
