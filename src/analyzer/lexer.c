/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 21:19:24 by ciglesia          #+#    #+#             */
/*   Updated: 2021/06/02 21:47:16 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** op: | < > >>
** param: 2 non-op (spc: "" '' $)
*/

static int	envar_len(char *s, int i, int dig)
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

static int	is_envar(char *s, int i)
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

static char	*escape_char(char *str, int i)
{
	if (!str[i + 1])
	{
		free(str);
		return (NULL);
	}
	if (str[i + 1] != '\'')
	{
		str[i] = '\'';
		str = ft_strins(str, "'", i + 2);
	}
	else
	{
		str[i] = '"';
		str = ft_strins(str, "\"", i + 2);
	}
	return (str);
}

/*
**	1 : env variable
**	2 : ? last status exit
**	3 : other variable
**	4 : number pos param variable
*/

static char	*replace_envar(char *str, int *i, int type)
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

/*
**	only in double quote \ escapes: \, " or $
*/
static char	*skip_quote(char *str, int *i, int dq)
{
	char	quote;
	int		envar;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
	{
		if (dq)
		{
			envar = is_envar(str, *i);
			if (str[*i] == '\\' && ft_countchr("\"\\$", str[*i + 1]))
			{
				str[*i] = 0;
				str = ft_fstrjoin(str, &str[(*i) + 1]);
			}
			else if (envar)
				str = replace_envar(str, i, envar);
		}
		(*i)++;
	}
	(*i)++;
	return (str);
}
/*
**	replace $envs and \escapes
*/

static char	*replace_envar_escape(char *str)
{
	int		i;
	int		envar;
	int		len;

	i = 0;
	while (str[i])
	{
		envar = is_envar(str, i);
		if (str[i] == '\'' || str[i] == '"')
			str = skip_quote(str, &i, str[i] == '"');
		else if (str[i] == '\\')
		{
			str = escape_char(str, i);
			if (!str)
				return (NULL);
			i += 3;
		}
		else if (envar)
			str = replace_envar(str, &i, envar);
		else
			i++;
	}
	return (str);
}

int	ft_lexer(int x)
{
	int		i;
	int		error;
	char	*str;

	str = g_sh->cmd_line[x];
	str = replace_envar_escape(str);
	g_sh->cmd_line[x] = str;
	if (str == NULL)
	{
		return ((int)ft_puterror(BOLD"lexical error near \
unexpected token\n", (void *)EXIT_FAILURE));
	}
	printf("STR: %s\n", str);
	//replace \escapes and $envs outside quotes
	//replace \escapes and $envs inside double quotes
	//extract tokens and replace quotes



/*
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
*/
	return (EXIT_SUCCESS);
}
