/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:04:34 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/23 13:18:13 by ciglesia         ###   ########.fr       */
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

void	print_btree(t_ast *node, char *prefix, t_uchar is_left)
{
	static char end[] = {0xe2,0x94,0x94,0xe2,0x94,0x80,0xe2,0x94,0x80,32,0x00};
	static char mid[] = {0xe2,0x94,0x8c,32,32,32,0x00};
	static char pip[] = {0xe2,0x94,0x82,32,32,32,0x00};
	static char *ops[] = {NULL,"<",">",">>","|"};
	char	*str;

	if (node)
	{
		if (is_left)
			str = mid;
		else
			str = end;
		if (node->bin)
			printf("%s%s"BOLD""BLUE"%s\n"E0M, prefix, str, node->bin);
		else
			printf("%s%s"BOLD""YELLOW"%s\n"E0M, prefix, str, ops[node->op]);
		if (is_left)
			str = ft_strjoin(prefix, pip);
		else
			str = ft_strjoin(prefix, "    ");
		print_btree(node->left, str, 1);
		print_btree(node->right, str, 0);
		free(str);
	}
}

static t_ast	*arrange_ast(t_ast *head)
{
	t_ast	*tmp;
	t_ast	*left;
	t_ast	*right;
	t_ast	*op;

	left = NULL;
	right = NULL;
	op = NULL;
	tmp = head;
	while (tmp)
	{
		if (!left && tmp->bin)
			left = tmp;
		else if (!tmp->bin)
		{
			if (op)
				tmp->left = op;
			op = tmp;
		}
		else if (!right && tmp->bin)
		{
			if (!op->left)
				op->left = left;
			op->right = tmp;
			left = op;
			right = NULL;
		}
		tmp = tmp->next;
	}
	return (op);
}

int	ft_parser(int x)
{
	t_ast	*tmp;
	int		i;
	t_ast	*op;

	construct_cmds(&g_sh->cmds[x]);
	op = arrange_ast(g_sh->cmds[x]);

	//printf(BLUE"parser: [%s] cmdid: %d\n"E0M, g_sh->cmd_line[x], x);
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
	if (op)
		g_sh->cmds[x] = op;
	print_btree(g_sh->cmds[x], "", 0);
	printf("\n");
	return (EXIT_SUCCESS);
}
