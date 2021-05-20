/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:16:39 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/20 00:58:26 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	sh_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		ft_putstr_fd(BOLD"minishell: pwd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n"E0M, 2);
		return (0);
	}
	printf("%s\n", tmp);
	free(tmp);
	return (1);
}
