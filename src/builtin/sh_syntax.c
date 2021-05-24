/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 08:55:38 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/24 09:24:32 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	sh_syntax(int ac, char	**av)
{
	if (ac > 2)
		return (EXIT_FAILURE);
	if (ft_strcmp(av[1], "on") && ft_strcmp(av[1], "off"))
		return (EXIT_FAILURE);
	if (!ft_strcmp(av[1], "on"))
		g_sh->syntax = 1;
	else
		g_sh->syntax = 0;
	return (EXIT_SUCCESS);
}
