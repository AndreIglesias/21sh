/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 21:19:24 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/21 01:40:48 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"


static int	ft_cspecial(const char *c)
{
	int i;

	i = 0;
	while (c[i] == ' ' || (c[i] >= 9 && c[i] <= 13))
		i++;
	return (i);
}

int		empty_cmds(void)
{
	int	i;
	int	spc;
	int	content;

	i = 0;
	spc = 0;
	content = 0;
	while (g_sh->line[i])
	{
		spc = ft_cspecial(&g_sh->line[i]);
		i += spc;
		if (g_sh->line[i])
		{
			if (g_sh->line[i] != ';')
				content++;
			else
			{
				if (!content)
					return (1);
				content = 0;
			}
			i++;
		}
	}
	return (0);
}



int	ft_lexer(void)
{
	int	c;

	if (empty_cmds())//verify inside quotes too and its consistency
		return ((int)ft_puterror(BOLD"minishell: syntax error near unexpected \
token `;'\n"E0M, (void*)EXIT_FAILURE));
	c = ft_countchr(g_sh->line, '"');
	if (c % 2 != 0)//verify its not inside single quotes ''
		return ((int)ft_puterror(BOLD"minishell: syntax error ending quote not \
found `\"'\n"E0M, (void*)EXIT_FAILURE));
	c = ft_countchr(g_sh->line, '\'');
	if (c % 2 != 0)//verify if not inside double quotes ""
		return ((int)ft_puterror(BOLD"minishell: syntax error ending quote not \
found `'\"\n"E0M, (void*)EXIT_FAILURE));
	c = ft_countchr(g_sh->line, ';');
	g_sh->cmds = new_astvec(ft_countchr(g_sh->line, ';'));
	printf(BLUE"lexer: [%s] cmds: %d\n"E0M, g_sh->line, c);
	return (0);
}
