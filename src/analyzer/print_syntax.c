/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:45:24 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/24 13:34:48 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_ast	*first_in_list(t_ast *node)
{
	while (node->back)
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
	static char end[] = {0xe2,0x94,0x94,0xe2,0x94,0x80,0xe2,0x94,0x80,32,0x00};
	static char mid[] = {0xe2,0x94,0x8c,32,32,32,0x00};
	static char pip[] = {0xe2,0x94,0x82,32,32,32,0x00};
	char	*str;

	if (node)
	{
		if (is_left)
			str = mid;
		else
			str = end;
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

static void	print_box(char *str)
{
	ft_putstr("[");
	ft_putstr(str);
	ft_putstr("] "E0M);
}

void	print_tokens(t_ast *tmp, int i)
{
	ft_putstr(BOLD"tokens: "E0M);
	while (tmp)
	{
		if (tmp->bin)
		{
			if (tmp->type < 3)
				ft_putstr(CEL);
			ft_putnbr(tmp->type);
			print_box(tmp->bin);
			i = 0;
			while (i < tmp->ac)
			{
				ft_putstr(BLUE);
				print_box(tmp->av[i]);
				i++;
			}
		}
		else
		{
			ft_putstr(BOLD""GRAY);
			print_box(g_sh->ops[tmp->op]);
		}
		tmp = tmp->next;
	}
	ft_putstr("\n");
}
