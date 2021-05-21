/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 21:19:24 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/22 00:12:27 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** op: | < > >>
** param: 2 non-op (spc: "" '' $)
*/

static char	*save_string(char *str, int i, char quote)// replace env var!
{
	char	*new;

	new = ft_fchrjoin(NULL, str[i++]);
	while (str[i] && str[i] != quote)
	{
		if (str[i] == '$')//$?
		new = ft_fchrjoin(new, str[i++]);
	}
	if (str[i] == quote)
		new = ft_fchrjoin(new, str[i++]);
	return (new);
}

static t_uchar	is_op(char *str)
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
		if (str[i])
			new = ft_fchrjoin(NULL, str[i++]);
		while (str[i] && !ft_cspecial(&str[i]) && !is_op(&str[i]))
			new = ft_fchrjoin(new, str[i++]);
		if (new)
			add_ast(&g_sh->cmds[x], new_astcmd(new, NULL));
	}
	return (i);
}

static int	save_envnode(char *str, int i, int x)
{
	char	*tmp;
	char	*string;
	int		c;
	int		k;

	c = 0;
	k = i;
	while (str[k] && !ft_cspecial(&str[k]) && !is_op(&str[k]))
	{
		k++;
		c++;
	}
	tmp = ft_strndup(&str[i + 1], c - 1);
	string = get_value(g_sh->ev, tmp);
	free(tmp);
	if (string)
		add_ast(&g_sh->cmds[x], new_astcmd(ft_strdup(string), NULL));
	else
		add_ast(&g_sh->cmds[x], new_astcmd(ft_strdup(""), NULL));
	return (k);
}

int	new_token(char *str, int i, int x)
{
	char	*string;

	if (str[i] == '\'')
	{
		string = save_string(str, i, '\'');
		i += ft_strlen(string);
		add_ast(&g_sh->cmds[x], new_astcmd(string, NULL));
	}
	else if (str[i] == '"')
	{
		string = save_string(str, i, '"');
		i += ft_strlen(string);
		add_ast(&g_sh->cmds[x], new_astcmd(string, NULL));
	}
	else if(str[i] == '$' && str[i + 1] && str[i + 1] != '?')//send $? to save_envnode
		i = save_envnode(str, i, x);
	else
		i = save_token(str, i, x);
	return (i);
}

static void	create_tokens(char *str, int x)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i += ft_cspecial(&str[i]);
		if (str[i])
			i = new_token(str, i, x);
	}
}

int	ft_lexer(int x)
{
	create_tokens(g_sh->cmd_line[x], x);
	return (EXIT_SUCCESS);
}
