/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:16:39 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/01 23:02:11 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sh_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		ft_putstr_fd(BOLD"minishell: pwd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n"E0M, 2);
		g_sh->last_status = 1;
	}
	else
	{
		printf("%s\n", tmp);
		free(tmp);
		g_sh->last_status = 0;
	}
}
