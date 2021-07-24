/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 19:17:09 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/24 21:43:14 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	print_pwd(char *pwd)
{
	char	*home;
	int		len;

	home = get_value(g_sh->ev, "HOME");
	len = 0;
	if (home)
		len = ft_strlen(home);
	ft_putstr(BOLD""GRAY);
	ft_putstr(BG_CYAN);
	if (home && !ft_strncmp(home, pwd, len))
	{
		ft_putstr(" ~");
		if (len && home[len - 1] == '/')
			ft_putchar('/');
		ft_putstr(&pwd[len]);
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

static void	second_status(void)
{
	char		*branch;
	static char	*cmd[] = {"/usr/bin/git","rev-parse","--abbrev-ref","HEAD", NULL};

	ft_putstr((char []){0xe2, 0x9d, 0xb1, 0x00});
	branch = xbuff(cmd, 0);
	porcelain_prompt(branch);
	free(branch);

}

void	ft_prompt(void)
{
	char		*user;
	char		*pwd;

	ft_putstr((char []){0xe2, 0x95, 0xad, 0xe2, 0x94, 0x80, 0x00});
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
		print_pwd(pwd);
	free(pwd);
	second_status();
	ft_putstr((char []){0xe2, 0x95, 0xb0, 0xe2, 0x97, 0xa0,
		0xe2, 0x97, 0xa1, 0x20, 0x00});
}
