/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 19:46:54 by ciglesia          #+#    #+#             */
/*   Updated: 2021/06/01 18:19:36 by user             ###   ########.fr       */
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

/*
**	tmp is the new op
**	add last op to the left if exists
*/

static void	add_op(t_ast **tmp, t_ast **op, t_ast *left, t_ast **left_op)
{
	if (*op)
		(*tmp)->left = *op;
	*op = *tmp;
	if (!left && (*op)->next && (*op)->next->bin)
	{
		(*op)->right = (*op)->next;
		*tmp = (*tmp)->next;
		*left_op = *op;
	}
}

/*
**	arrange list of cmds to form a subtree of redirections
**	left && tmp->bin is THE command
*/

t_ast	*arrange_ast(t_ast *head, t_ast *left, t_ast *op, t_uchar opp)
{
	t_ast	*tmp;
	t_ast	*left_op;

	tmp = head;
	left_op = NULL;
	while (tmp && tmp->op != opp)
	{
		if (!left && tmp->bin)
		{

			left = tmp;
			if (left_op && op)
				op->left = left;
			left_op = NULL;
		}
		else if (!tmp->bin)
		{
			add_op(&tmp, &op, left, &left_op);
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
