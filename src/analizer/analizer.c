/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analizer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 21:05:45 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/21 16:18:17 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	ft_cspecial(const char *c)
{
	int i;

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

static int	consistent_cmd(void)
{
	int	sq;
	int	dq;
	int	i;
	int	content;

	i = 0;
	sq = 0;
	dq = 0;
	content = 0;
	while (g_sh->line[i])
	{
		i += ft_cspecial(&g_sh->line[i]);
		if (g_sh->line[i])
		{
			g_sh->ncmd = consistency(&sq, &dq, &content, i);
			if (!g_sh->ncmd)
				return (0);
			i++;
		}
	}
	if (dq || sq)
		return ((int)ft_puterror(BOLD"minishell: syntax error ending quote not \
found `\"'\n"E0M, (void*)0));
	return (1);
}

static void	save_cmds(void)
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
}

void	ft_analizer(void)
{
	int	i;

	g_sh->ncmd = 1;
	if (!consistent_cmd())
		return ;
	g_sh->cmd_line = malloc(sizeof(char *) * (g_sh->ncmd + 1));
	i = 0;
	while (i < g_sh->ncmd + 1)
		g_sh->cmd_line[i++] = NULL;
	save_cmds();
	i = 0;
	while (g_sh->cmd_line[i])
		i++;
	g_sh->ncmd = i;
	g_sh->cmds = new_astvec(g_sh->ncmd);
	i = 0;
	while (g_sh->cmd_line[i])
	{
		if (ft_lexer(i) == EXIT_FAILURE)
			return ;
		i++;
	}
}
