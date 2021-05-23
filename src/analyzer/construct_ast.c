/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 19:46:54 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/23 20:23:11 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	add_ast(t_ast **head, t_ast *node)
{
	int		i;
	t_ast	*tmp;

	if (*head == NULL)
		*head = node;
	else
	{
		i = 0;
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		node->back = tmp;
	}
}

static void	add_children(t_ast *op, t_ast *left, t_ast *right)
{
	if (!op->left && left)
		op->left = left;
	if (right)
		op->right = right;
}

static void	add_op(t_ast **tmp, t_ast **op, t_ast *left, t_ast *head)
{
	if (*op)
		(*tmp)->left = *op;
	*op = *tmp;
	if ((*op == head || (*op != head && !left))
		&& (*op)->next && (*op)->next->bin)
	{
		(*op)->right = (*op)->next;
		*tmp = (*tmp)->next;
	}
}

t_ast	*arrange_ast(t_ast *head, t_ast *left, t_ast *op)
{
	t_ast	*tmp;

	tmp = head;
	while (tmp)
	{
		if (!left && tmp->bin)
			left = tmp;
		else if (!tmp->bin)
		{
			add_op(&tmp, &op, left, head);
			if (!op->next)
				add_children(op, left, NULL);
		}
		else
		{
			add_children(op, left, tmp);
			left = op;
		}
		tmp = tmp->next;
	}
	return (op);
}
