/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 19:18:10 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/23 19:47:09 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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
			if (str[*i] == '\\' && ft_countchr("\\$", str[*i + 1]))
			{
				str[*i] = 0;
				str = ft_fstrjoin(str, &str[(*i) + 1]);
			}
			else if (envar)
			{
				str = replace_envar(str, i, envar);
				(*i)--;
			}
		}
		(*i)++;
	}
	(*i)++;
	return (str);
}

/*
**	replace \escapes, $envs and ~
*/

static char	*replace_envar_escape(char *str)
{
	int		i;
	int		envar;

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
		else if (str[i] == '~')
			str = replace_home(str, &i);
		else
			i++;
	}
	return (str);
}

int	ft_lexer(int x)
{
	g_sh->cmd_line[x] = replace_envar_escape(g_sh->cmd_line[x]);
	if (g_sh->cmd_line[x] == NULL)
	{
		return ((int)ft_puterror(BOLD"lexical error near \
unexpected token\n", (void *)EXIT_FAILURE));
	}
	extract_tokens(g_sh->cmd_line[x], x);
	return (EXIT_SUCCESS);
}
