/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 12:54:30 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/25 13:36:33 by ciglesia         ###   ########.fr       */
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

void	ft_prompt(void)
{
	char		*user;
	char		*pwd;
	static char	point[] = {32,0xe2,0x9d,0xb1,32,0x00};

	user = get_value(g_sh->ev, "USER");
	pwd = getcwd(NULL, 0);
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
		print_pwd(pwd);
	if (user || pwd)
		ft_putstr(point);
	else
		ft_putstr(BOLD" $ "E0M);
}
