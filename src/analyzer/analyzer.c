/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 23:56:02 by ciglesia          #+#    #+#             */
/*   Updated: 2021/06/03 01:04:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	ft_cspecial(const char *c)
{
	int	i;

	i = 0;
	while (c[i] == ' ' || (c[i] >= 9 && c[i] <= 13))
		i++;
	return (i);
}

static int	consistency(int *sq, int *dq, int *content, int i)
{
	if (g_sh->line[i] == '\'' && !*dq)
	{
		*sq = (*sq + 1) % 2;
		*content = 1;
	}
	else if (g_sh->line[i] == '"' && !*sq)
	{
		*dq = (*dq + 1) % 2;
		*content = 1;
	}
	else if (g_sh->line[i] == ';' && !*sq && !*dq && *content)
	{
		g_sh->ncmd++;
		*content = 0;
	}
	else if (g_sh->line[i] == ';' && !*sq && !*dq && !*content)
	{
		return ((int)ft_puterror(BOLD"minishell: syntax error near unexpected \
token `;'\n"E0M, (void *)0));
	}
	else
		*content = 1;
	return (g_sh->ncmd);
}

static int	consistent_cmd(int i)
{
	int	sq;
	int	dq;
	int	content;

	sq = 0;
	dq = 0;
	content = 0;
	while (g_sh->line[i])
	{
		i += ft_cspecial(&g_sh->line[i]);
		if (g_sh->line[i] && g_sh->line[i] == '\\' && !sq)
			i += 1 + (g_sh->line[i + 1] != 0);
		else if (g_sh->line[i])
		{
			g_sh->ncmd = consistency(&sq, &dq, &content, i);
			if (!g_sh->ncmd)
				return (0);
			i++;
		}
	}
	if (dq || sq)
		return ((int)ft_puterror(BOLD"minishell: syntax error ending quote not \
found `\"'\n"E0M, (void *)0));
	return (1);
}

static void	save_lines(void)
{
	int	sq;
	int	dq;
	int	i;
	int	x;

	i = 0;
	sq = 0;
	dq = 0;
	x = 0;
	while (g_sh->line[i])
	{
		if (g_sh->line[i] == '\'' && !dq)
			sq = (sq + 1) % 2;
		else if (g_sh->line[i] == '"' && !sq)
			dq = (dq + 1) % 2;
		if (g_sh->line[i] == ';' && !sq && !dq)
			x++;
		else
			g_sh->cmd_line[x] = ft_fchrjoin(g_sh->cmd_line[x], g_sh->line[i]);
		i++;
	}
	i = 0;
	while (g_sh->cmd_line[i])
		i++;
	g_sh->ncmd = i;
}

int	ft_analyze(void)
{
	int	i;

	g_sh->ncmd = 1;
	if (!consistent_cmd(0))
		return (EXIT_FAILURE);
	g_sh->cmd_line = ft_memalloc(sizeof(char *) * (g_sh->ncmd + 1));
	save_lines();
	g_sh->cmds = new_astvec(g_sh->ncmd);
	i = 0;
	while (g_sh->cmd_line[i])
	{
		if (ft_lexer(i) == EXIT_FAILURE || ft_parser(i) == EXIT_FAILURE)
		{
			if (g_sh->cmds[i])
				g_sh->cmds[i]->valid = 0;
			g_sh->last_status = EXIT_FAILURE;
		}
		else
		ft_semantic(i);
		i++;
	}
	free_cmd_line();
	return (EXIT_SUCCESS);
}
