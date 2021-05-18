/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 12:54:30 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/18 13:59:36 by ciglesia         ###   ########.fr       */
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

void	ft_prompt(t_shell *sh)
{
	char	*user;
	char	*pwd;

	user = get_value(sh->ev, "USER");
	pwd = get_value(sh->ev, "PWD");
	if (user)
	{
		ft_putstr(GREEN""BOLD);
		ft_putstr(user);
		ft_putstr(E0M);
	}
	if (user && pwd)
		ft_putstr(BOLD" | "E0M);
	if (pwd)
	{
		ft_putstr(BOLD""BLUE"~/");
		ft_putstr(remove_home(pwd));
		ft_putstr(E0M);
	}
	if (user || pwd)
		ft_putstr(BOLD" > "E0M);
	else
		ft_putstr(BOLD" $ "E0M);
}
