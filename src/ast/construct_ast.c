/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 19:46:54 by ciglesia          #+#    #+#             */
/*   Updated: 2021/06/04 18:38:07 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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
	}
	if (*op && *left)
	{
		add_children(*op, *left, NULL);
		*left = *op;
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
**	appends the < redirection to the command and continues
*/

static void	add_left_op(t_ast *cmd, t_ast **left_op, t_ast **op, t_ast *left)
{
	if (cmd && *left_op)
	{
		add_to_cmd(cmd, *left_op);
		*op = left;
		*left_op = NULL;
	}
}

static void	arranges_op_cmd(t_ast **left_op, t_ast *op,
							t_ast **left, t_ast *cmd)
{
	*left = cmd;
	if (*left_op && op && op->op != 1)
		op->left = cmd;
	else if (*left_op)
		add_to_cmd(cmd, *left_op);
	*left_op = NULL;
}

/*
**	arrange list of cmds to form a subtree of redirections
**	left && tmp->bin is THE command
**	while op != 4 (pipe)
*/

t_ast	*arrange_ast(t_ast *tmp, t_ast *left, t_ast *op, t_ast *cmd)
{
	t_ast	*left_op;

	left_op = NULL;
	while (tmp && tmp->op != 4)
	{
		if (!left && tmp->bin)
		{
			cmd = tmp;
			arranges_op_cmd(&left_op, op, &left, cmd);
		}
		else if (!tmp->bin)
		{
			if (!add_op(&tmp, &op, &left, &left_op))
				return (NULL);
			add_left_op(cmd, &left_op, &op, left);
		}
		if (tmp)
			tmp = tmp->next;
	}
	if (!op)
		return (left);
	return (op);
}
