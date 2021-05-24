/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 00:00:07 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/25 00:13:35 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	is_bin(t_ast *node)
{
	char	*str;
	if (is_builtin(node->bin))
		node->type = 1;
	else
	{
		str = sh_which(node->bin, g_sh->ev);
		if (str)
		{
			node->type = 2;
			free (node->bin);
			node->bin = str;
		}
		else
			return (0);
	}
	return (1);
}

static int	is_pipe(t_ast *node)
{
	if (!node->right || !node->left || node->right->type == 4)
	{
		ft_puterror(BOLD"minishell: syntax error inconsistent pipe\n", NULL);
		return (0);
	}
	if (node->right && node->right->bin && !is_bin(node->right))
	{
		ft_puterror(BOLD"minishell: semantic error after pipe:", NULL);
		if (node->left && node->left->bin)
		{
			ft_putstr_fd(" "BLUE, 2);
			ft_putstr_fd(node->right->bin, 2);
			ft_putstr_fd(E0M""BOLD, 2);
		}
		ft_puterror(" command not found\n"E0M, NULL);
		node->right->type = 0;
	}
	return (1);
}

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

static int	consistent_types(t_ast **node)
{
	int		i;

	i = 1;
	if (node && *node)
	{
		if ((*node)->bin && !is_bin(*node))
		{
			ft_puterror(BOLD"minishell: ", NULL);
			ft_putstr_fd(BLUE, 2);
			ft_putstr_fd((*node)->bin, 2);
			ft_puterror(E0M""BOLD": command not found\n"E0M, NULL);
			return (0);
		}
		else if ((*node)->op == 4 && !is_pipe(*node))
			return (0);
		else if ((*node)->op == 1 && !right_file(*node))
			return (0);
		else if (((*node)->op == 2 || (*node)->op == 3) && !left_cmd(*node))
			return (0);
		i *= consistent_types(&((*node)->left));
		i *= consistent_types(&((*node)->right));
	}
	return (i);
}

int	ft_semantic(int x)
{
	print_tokens(first_in_list(g_sh->cmds[x], -1), 0, -1);
	print_btree(g_sh->cmds[x], "", 0);
	ft_putstr("\n");
	if (!consistent_types(&g_sh->cmds[x]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
