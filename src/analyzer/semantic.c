/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 00:00:07 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/25 19:22:52 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	right_file(t_ast *node)
{
	if (!node->right || !node->right->bin || !is_file(node->right->bin))
	{
		ft_puterror(BOLD"minishell: semantic error:", NULL);
		if (node->right && node->right->bin)
		{
			ft_putstr_fd(" "BLUE, 2);
			ft_putstr_fd(node->right->bin, 2);
			ft_putstr_fd(E0M""BOLD":", 2);
		}
		ft_puterror(" No such file or directory\n"E0M, NULL);
		return (0);
	}
	if (node->right)
		node->right->type = 3;
	return (1);
}

static int	left_cmd(t_ast *node)
{
	if (node->left == NULL)
		return (1);
	if (node->left->bin && !is_bin(node->left))
	{
		ft_puterror(BOLD"minishell: ", NULL);
		ft_putstr_fd(BLUE, 2);
		ft_putstr_fd(node->left->bin, 2);
		ft_puterror(E0M""BOLD": command not found\n"E0M, NULL);
		return (0);
	}
	if (node->right)
		node->right->type = 4;
	if (!node->left->bin)
		return (1);
	return (1);
}

static int	consistent_subtrees(t_ast *node)
{
	int		i;

	i = 1;
	if (node)
	{
		if (node->bin && !is_bin(node))
		{
			ft_puterror(BOLD"minishell: ", NULL);
			ft_putstr_fd(BLUE, 2);
			ft_putstr_fd(node->bin, 2);
			ft_puterror(E0M""BOLD": command not found\n"E0M, NULL);
			return (0);
		}
		else if (node->op == 1 && !right_file(node))
			return (0);
		else if ((node->op == 2 || node->op == 3) && !left_cmd(node))
			return (0);
		i *= consistent_subtrees(node->left);
		i *= consistent_subtrees(node->right);
	}
	return (i);
}

static int	consistent_trees(t_ast *node)
{
	int	i;

	i = 1;
	if (node)
	{
		if (node->op == 4)
		{
			if (!is_pipe(node))
				return (0);
			if (node->right)
				return (consistent_subtrees(node->right));
			if (node->left && node->op == 4)
				i *= consistent_trees(node->left);
			else if (node->left)
				return (consistent_subtrees(node->left));
		}
		else
			return (consistent_subtrees(node));
	}
	return (i);
}

int	ft_semantic(int x)
{
	print_tokens(first_in_list(g_sh->cmds[x], -1), 0, -1);
	print_btree(g_sh->cmds[x], "", 0);
	ft_putstr("\n");
	if (!consistent_trees(g_sh->cmds[x]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
