/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 21:19:24 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/23 21:29:51 by ciglesia         ###   ########.fr       */
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

static int	end_of_token(char *str, int i, char quote)
{
	if (str[i] && (quote || (!ft_cspecial(&str[i]) && !is_op(&str[i])
				&& (str[i] != '$' || str[i + 1] == '$' || !str[i + 1]))))
		return (1);
	return (0);
}

static int	save_token(char *str, int i, int x)
{
	char	*new;
	t_uchar	op;
	char	quote;

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
					new = ft_fchrjoin(new, str[i++]);
				i++;
				continue ;
			}
			new = ft_fchrjoin(new, str[i++]);
		}
		if (new)
			add_ast(&g_sh->cmds[x], new_astcmd(new, NULL));
		else
			return (-1);
	}
	return (i);
}

static int	new_token(char *str, int i, int x)
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
	else if(is_envar(str, i, 0))
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
			error = new_token(str, i, x);
			if (error < 0)
				return ((int)ft_puterror(BOLD"lexical error near \
unexpected token\n", (void *)EXIT_FAILURE));
			i = error;
		}
	}
	return (EXIT_SUCCESS);
}
