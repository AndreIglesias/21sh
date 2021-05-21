/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 21:19:24 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/21 19:34:58 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** op: | < > >>
** param: 2 non-op (spc: "" '' $)
*/

static char	*save_string(char *str, int i, char quote)
{
	char	*new;

	new = ft_fchrjoin(NULL, str[i++]);
	while (str[i] && str[i] != quote)
		new = ft_fchrjoin(new, str[i++]);
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
	t_ast	*tmp;

	create_tokens(g_sh->cmd_line[x], x);
	printf(BLUE"lexer: [%s] cmdid: %d\n"E0M, g_sh->cmd_line[x], x);
	ft_putstr(E0M"tokens: ");
	tmp = g_sh->cmds[x];
	while (tmp)
	{
		if (tmp->bin)
		{
			ft_putstr(YELLOW"[");
			ft_putstr(tmp->bin);
		}
		else
		{
			ft_putstr(GREEN"[");
			ft_putnbr(tmp->op);
		}
		ft_putstr("] "E0M);
		tmp = tmp->next;
	}
	ft_putstr("\n");
	return (0);
}
