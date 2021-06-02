/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <ciglesia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 00:36:03 by user              #+#    #+#             */
/*   Updated: 2021/06/03 00:47:55 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** op: | < > >>
** param: 2 non-op (spc: "" '' $)
*/

int	envar_len(char *s, int i, int dig)
{
	int	len;

	i++;
	len = i;
	while (s[i] && ((!dig && (ft_isalpha(s[i]) || s[i] == 95))
										|| ft_isdigit(s[i])))
		i++;
	len = i - len;
	return (len);
}

/*
**	1 : env variable
**	2 : ? last status exit
**	3 : other variable
**	4 : number pos param variable
*/

int	is_envar(char *s, int i)
{
	if (s[i] && s[i] == '$' && s[i + 1])
	{
		i++;
		if (s[i] == '?')
			return (2);
		else if (ft_countchr("*@#-$!", s[i]))
			return (3);
		else if (ft_isdigit(s[i]))
			return (4);
		else if (ft_isalpha(s[i]) || s[i] == 95)
			return (1);
	}
	return (0);
}

static char	*extract_string(char *token, int *j, int *poped)
{
	if (token[*j] == '\'')
	{
		token = ft_strpop(token, *j);
		while (token[*j] && token[*j] != '\'')
			(*j)++;
		token = ft_strpop(token, *j);
	}
	else if (token[*j] == '"')
	{
		token = ft_strpop(token, *j);
		while (token[*j] && token[*j] != '"')
		{
			if (token[*j] == '\\')
			{
				token = ft_strpop(token, *j);
				(*j)++;
				(*poped)++;
			}
			if (token[*j])
				(*j)++;
		}
		token = ft_strpop(token, *j);
	}
	(*poped) += 2;
	return (token);
}

static int	extract_word(char *str, int i, int x)
{
	char	*token;
	int		poped;
	int		j;

	token = ft_strdup(&str[i]);
	poped = 0;
	j = 0;
	while (token[j] && !ft_countchr("<>|", token[j]) && !ft_cspecial(&token[j]))
	{
		if (token[j] == '\'' || token[j] == '"')
			token = extract_string(token, &j, &poped);
		else
			j++;
	}
	token[j] = 0;
	add_ast(&g_sh->cmds[x], new_astcmd(token, NULL));
	return (i + j + poped);
}

void	extract_tokens(char *str, int x)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i += ft_cspecial(&str[i]);
		if (ft_countchr("<>|", str[i]))
		{
			add_ast(&g_sh->cmds[x], new_astop(is_op(&str[i])));
			if (is_op(&str[i]) == 3)
				i++;
			i++;
		}
		else if (str[i])
			i = extract_word(str, i, x);
	}
}
