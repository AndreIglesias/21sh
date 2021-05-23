/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 12:54:30 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/23 18:43:47 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*remove_home(char *dir)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (dir[i] && c < 3)
	{
		if (dir[i] == '/')
			c++;
		i++;
	}
	if (c < 3)
		return (dir);
	return (&dir[i]);
}

static void	print_pwd(char *pwd)
{
	char	*home;

	home = get_value(g_sh->ev, "HOME");
	ft_putstr(BOLD""BLUE);
	if (home && !ft_strncmp(home, pwd, ft_strlen(home)))
	{
		ft_putstr("~/");
		ft_putstr(remove_home(pwd));
	}
	else
		ft_putstr(pwd);
	ft_putstr(E0M);
}

void	ft_prompt(void)
{
	char		*user;
	char		*pwd;
	static char bar[] = {32,0xe2,0x9d,0x99,32,0x00};
	static char	point[] = {32,0xe2,0x9d,0xb1,32,0x00};

	user = get_value(g_sh->ev, "USER");
	pwd = getcwd(NULL, 0);
	if (user)
	{
		ft_putstr(GREEN""BOLD);
		ft_putstr(user);
		ft_putstr(E0M);
	}
	if (user && pwd)
		ft_putstr(bar);
	if (pwd)
		print_pwd(pwd);
	if (user || pwd)
		ft_putstr(point);
	else
		ft_putstr(BOLD" $ "E0M);
}
