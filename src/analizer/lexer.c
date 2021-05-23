/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 21:19:24 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/23 18:57:29 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** op: | < > >>
** param: 2 non-op (spc: "" '' $)
*/

t_uchar	is_op(char *str)
{
	if (str && str[0])
	{
		if (str[0] == '<')
			return (1);
		if (str[0] == '>' && str[1] && str[1] == '>')
			return (3);
		if (str[0] == '>')
			return (2);
		if (str[0] == '|')
			return (4);
	}
	return (0);
}

static char	*save_string(char *str, int *i, char quote)
{
	char	*new;
	int		k;

	new = ft_fchrjoin(NULL, str[(*i)++]);
	while (str[*i] && str[*i] != quote)
	{
		if (is_envar(str, *i, quote))
		{
			k = (*i);
			new = string_envar(str, new, &k, quote);
			(*i) = k;
		}
		else
			new = ft_fchrjoin(new, str[(*i)++]);
	}
	if (str[*i] == quote)
		new = ft_fchrjoin(new, str[(*i)++]);
	return (new);
}

static int	end_of_token(char *str, int i)
{
	if (str[i] && !ft_cspecial(&str[i]) && !is_op(&str[i])
		&& (str[i] != '$' || str[i + 1] == '$' || !str[i + 1]))
		return (1);
	return (0);
}

static int	save_token(char *str, int i, int x)
{
	char	*new;
	t_uchar	op;

	op = is_op(&str[i]);
	if (op)
	{
		add_ast(&g_sh->cmds[x], new_astop(op));
		if (op == 3)
			i += 2;
		else
			i++;
	}
	else
	{
		new = NULL;
		while (end_of_token(str, i))
			new = ft_fchrjoin(new, str[i++]);
		if (new)
			add_ast(&g_sh->cmds[x], new_astcmd(new, NULL));
	}
	return (i);
}

static int	new_token(char *str, int i, int x)
{
	char	*string;

	if (str[i] == '\'')
	{
		string = save_string(str, &i, '\'');
		add_ast(&g_sh->cmds[x], new_astcmd(string, NULL));
	}
	else if (str[i] == '"')
	{
		string = save_string(str, &i, '"');
		add_ast(&g_sh->cmds[x], new_astcmd(string, NULL));
	}
	else if(is_envar(str, i, 0))
		i = save_envnode(str, i, x);
	else
		i = save_token(str, i, x);
	return (i);
}

int	ft_lexer(int x)
{
	int		i;
	char	*str;

	str = g_sh->cmd_line[x];
	i = 0;
	while (str[i])
	{
		i += ft_cspecial(&str[i]);
		if (str[i])
			i = new_token(str, i, x);
	}
	return (EXIT_SUCCESS);
}
