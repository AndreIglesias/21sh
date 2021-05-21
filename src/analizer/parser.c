/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:04:34 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/21 23:44:41 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*extract_param(t_ast *tmp)
{
	char	*str;

	str = ft_strdup(tmp->bin);
	delete_astnode(tmp);
	return (str);

}

static t_ast	*add_param(t_ast *cmd)
{
	t_ast	*tmp;
	int		c;

	c = 0;
	tmp = cmd->next;
	while (tmp && tmp->bin)
	{
		c++;
		tmp = tmp->next;
	}
	if (c)
	{
		cmd->av = ft_memalloc(sizeof(char *) * (c + 1));
		cmd->ac = c;
		c = 0;
		tmp = cmd->next;
		while (tmp && tmp->bin)
		{
			cmd->av[c++] = extract_param(tmp);
			tmp = tmp->next;
		}
	}
	return (tmp);
}

static void	construct_cmds(t_ast **head)
{
	t_ast	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->bin)
			tmp = add_param(tmp);
		else
			tmp = tmp->next;
	}
}

int	ft_parser(int x)
{
	t_ast	*tmp;
	int		i;

	construct_cmds(&g_sh->cmds[x]);
	printf(BLUE"parser: [%s] cmdid: %d\n"E0M, g_sh->cmd_line[x], x);
	ft_putstr(E0M"tokens: ");
	tmp = g_sh->cmds[x];
	while (tmp)
	{
		if (tmp->bin)
		{
			ft_putstr(YELLOW"[");
			ft_putstr(tmp->bin);
			ft_putstr("] "E0M);
			i = 0;
			while (i < tmp->ac)
			{
				ft_putstr(CYAN"[");
				ft_putstr(tmp->av[i]);
				ft_putstr("] "E0M);
				i++;
			}
		}
		else
		{
			ft_putstr(GREEN"[");
			ft_putnbr(tmp->op);
			ft_putstr("] "E0M);
		}
		tmp = tmp->next;
	}
	ft_putstr("\n");
	return (EXIT_SUCCESS);
}
