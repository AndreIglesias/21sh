/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:40:33 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/29 15:03:50 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_ast	*first_in_list(t_ast *node, t_uchar opp)
{
	if (!node)
		return (NULL);
	while (node->back && node->back->op != opp)
		node = node->back;
	return (node);
}

static void	print_branch(char *prefix, char *str, char *node, char *color)
{
	ft_putstr(prefix);
	ft_putstr(str);
	ft_putstr(BOLD);
	ft_putstr(color);
	ft_putstr(node);
	ft_putstr("\n"E0M);
}

void	print_btree(t_ast *node, char *prefix, t_uchar is_left)
{
	static char	end[] = {0xe2, 0x94, 0x94, 0xe2, 0x94, 0x80,
						0xe2, 0x94, 0x80, 32, 0x00};
	static char	mid[] = {0xe2, 0x94, 0x8c, 32, 32, 32, 0x00};
	static char	pip[] = {0xe2, 0x94, 0x82, 32, 32, 32, 0x00};
	char		*str;

	if (node)
	{
		str = end;
		if (is_left)
			str = mid;
		if (node->bin && node->type < 3)
			print_branch(prefix, str, node->bin, BLUE);
		else if (node->bin)
			print_branch(prefix, str, node->bin, "");
		else
			print_branch(prefix, str, g_sh->ops[node->op], YELLOW);
		if (is_left)
			str = ft_strjoin(prefix, pip);
		else
			str = ft_strjoin(prefix, "    ");
		print_btree(node->left, str, 1);
		print_btree(node->right, str, 0);
		free(str);
	}
}

static void	print_box(char *str, int type)
{
	static char	pip[] = {0xe2, 0x94, 0x82, 32, 32, 32, 0x00};

	if (type >= 0)
	{
		ft_putstr("\n");
		ft_putstr(pip);
		ft_putstr("\t");
	}
	ft_putstr("[");
	ft_putstr(str);
	if (type >= 0)
	{
		ft_putstr("|");
		ft_putnbr(type);
	}
	ft_putstr("] "E0M);
}

void	print_tokens(t_ast *tmp, int i, t_uchar opp)
{
	ft_putstr(BOLD"tokens: "E0M);
	while (tmp && tmp->op != opp)
	{
		if (tmp->bin)
		{
			if (tmp->type < 3)
				ft_putstr(CEL);
			print_box(tmp->bin, tmp->type);
			i = 0;
			while (i < tmp->ac)
			{
				ft_putstr(BLUE);
				print_box(tmp->av[i], -1);
				i++;
			}
		}
		else
		{
			ft_putstr(BOLD""LIGHT_GRAY);
			print_box(g_sh->ops[tmp->op], -1);
		}
		tmp = tmp->next;
	}
	ft_putstr("\n");
}
