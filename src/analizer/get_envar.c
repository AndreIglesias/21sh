/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:41:38 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/22 19:46:34 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"


int	is_envar(char *str, int i, char q)
{
	if (str[i] && str[i] == '$' && str[i + 1] && !is_op(&str[i + 1])
		&& !ft_cspecial(&str[i + 1]) && str[i + 1] != '$')
	{
		if (q && str[i + 1] == q)
			return (0);
		return (1);
	}
	return (0);
}

static char	*get_envnode(char *str, int i, int *k, char q)
{
	char	*tmp;
	char	*string;
	int		c;

	c = 0;
	*k = i;
	while (str[*k] && !ft_cspecial(&str[*k]) && !is_op(&str[*k]))
	{
		if (q && str[*k] == q)
			break ;
		(*k)++;
		c++;
		if (str[*k] == '$')
			break;
	}
	tmp = ft_strndup(&str[i + 1], c - 1);
	string = get_value(g_sh->ev, tmp);
	free(tmp);
	return (string);
}

char	*string_envar(char *str, char *new, int *i, char quote)
{
	int		k;
	char	*string;

	if (str[(*i) + 1] == '?')
	{
		new = ft_fchrjoin(new, g_sh->last_status + '0');
		(*i) += 2;
		return (new);
	}
	string = get_envnode(str, *i, &k, quote);
	if (string)
		new = ft_fstrjoin(new, string);
	(*i) = k;
	return (new);
}

int	save_envnode(char *str, int i, int x)
{
	char	*string;
	int		k;

	if (str[i + 1] == '?')
	{
		string = ft_fchrjoin(NULL, g_sh->last_status + '0');
		add_ast(&g_sh->cmds[x], new_astcmd(string, NULL));
		return (i + 2);
	}
	string = get_envnode(str, i, &k, 0);
	if (string)
		add_ast(&g_sh->cmds[x], new_astcmd(ft_strdup(string), NULL));
	else
		add_ast(&g_sh->cmds[x], new_astcmd(ft_strdup(""), NULL));
	return (k);
}
