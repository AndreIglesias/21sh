/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 19:46:30 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/23 19:49:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	1 : env variable
**	2 : ? last status exit
**	3 : other variable
**	4 : number pos param variable
*/

char	*replace_envar(char *str, int *i, int type)
{
	int		len;
	char	*var;
	char	*value;

	len = 1;
	if (type == 1 || type == 4)
		len = envar_len(str, *i, type == 4);
	if (type == 1)
	{
		var = ft_strndup(&str[(*i) + 1], len);
		value = get_value(g_sh->ev, var);
	}
	str[*i] = 0;
	str = ft_fstrjoin(str, &str[(*i) + len + 1]);
	if (type == 2)
	{
		var = ft_itoa(g_sh->last_status);
		value = var;
	}
	else if (type != 1)
		return (str);
	str = ft_strins(str, value, *i);
	(*i) += ft_strlen(value);
	free(var);
	return (str);
}

char	*replace_home(char *str, int *i)
{
	char	*home;

	if (*i && (str[(*i) - 1] != ' ' || (str[(*i) + 1]
				&& (str[(*i) + 1] != ' ' && str[(*i) + 1] != '/'))))
	{
		(*i)++;
		return (str);
	}
	home = get_value(g_sh->ev, "HOME");
	str[*i] = 0;
	str = ft_fstrjoin(str, &str[(*i) + 1]);
	str = ft_strins(str, home, *i);
	(*i) += ft_strlen(home);
	return (str);
}
