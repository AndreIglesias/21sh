/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 19:46:54 by ciglesia          #+#    #+#             */
/*   Updated: 2021/06/03 18:22:17 by user             ###   ########.fr       */
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

static void	add_to_cmd(t_ast *cmd, t_ast *op)
{
	t_ast	*tmp;

	if (!cmd->right)
	{
		cmd->right = op;
		return ;
	}
	tmp = cmd->right;
	while (tmp && tmp->left)
		tmp = tmp->left;
	tmp->left = op;
}

/*
**	tmp is the new op
**	add last op to the left if exists
**	if > >> add to pipe subtree < add to cmd subtree
*/

static int	add_op(t_ast **tmp, t_ast **op, t_ast **left, t_ast **left_op)
{
	if ((*tmp)->op != 1)
	{
		if (*op)
			(*tmp)->left = *op;
		*op = *tmp;
		if (*left)
		{
			add_children(*op, *left, NULL);
			*left = *op;
		}
	}
	if (!*left || (*tmp)->op == 1)
		*left_op = *tmp;
	if ((*tmp)->next && (*tmp)->next->bin)
	{
		(*tmp)->right = (*tmp)->next;
		*tmp = (*tmp)->next;
	}
	else if (!(*tmp)->next)
	{
		ft_puterror(SYE"inconsistent redirection `"BLUE, NULL);
		ft_puterror(g_sh->ops[(*tmp)->op], NULL);
		return ((int)ft_puterror(COLOR_E0M"'\n"E0M, NULL));
	}
	return (1);
}

/*
**	arrange list of cmds to form a subtree of redirections
**	left && tmp->bin is THE command
*/

t_ast	*arrange_ast(t_ast *head, t_ast *left, t_ast *op, t_uchar opp)
{
	t_ast	*tmp;
	t_ast	*left_op;
	t_ast	*cmd;

	tmp = head;
	left_op = NULL;
	cmd = NULL;
	while (tmp && tmp->op != opp)
	{
		if (!left && tmp->bin)//cmd
		{
			cmd = tmp;
			left = tmp;
			if (left_op && op && op->op != 1)
				op->left = left;
			else if (left_op)
				add_to_cmd(cmd, left_op);
			left_op = NULL;
		}
		else if (!tmp->bin)//op
		{
			if (!add_op(&tmp, &op, &left, &left_op))
				return (NULL);
			if (cmd && left_op)
			{
				add_to_cmd(cmd, left_op);
				op = left;
				left_op = NULL;
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
	if (!op)
		return (left);
	return (op);
}
