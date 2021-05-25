/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 21:19:24 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/25 19:06:54 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** op: | < > >>
** param: 2 non-op (spc: "" '' $)
*/

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

static int	extract_token(char *str, int i, char **new)
{
	int	quote;

	*new = NULL;
	quote = 0;
	while (end_of_token(str, i, quote))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!quote)
				quote = str[i];
			else if (str[i] == quote)
				quote = 0;
			else
				*new = ft_fchrjoin(*new, str[i++]);
			i++;
			continue ;
		}
		*new = ft_fchrjoin(*new, str[i++]);
	}
	return (i);
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
		i = extract_token(str, i, &new);
		if (new)
			add_ast(&g_sh->cmds[x], new_astcmd(new, NULL));
		else
			return (-1);
	}
	return (i);
}

static int	token_list(char *str, int i, int x)
{
	char	*string;
	int		error;

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
	else if (is_envar(str, i, 0))
		i = save_envnode(str, i, x);
	else
	{
		error = save_token(str, i, x);
		if (error < 0)
			return (-1);
		i = error;
	}
	return (i);
}

int	ft_lexer(int x)
{
	int		i;
	int		error;
	char	*str;

	str = g_sh->cmd_line[x];
	i = 0;
	while (str[i])
	{
		i += ft_cspecial(&str[i]);
		if (str[i])
		{
			error = token_list(str, i, x);
			if (error < 0)
				return ((int)ft_puterror(BOLD"lexical error near \
unexpected token\n", (void *)EXIT_FAILURE));
			i = error;
		}
	}
	return (EXIT_SUCCESS);
}
