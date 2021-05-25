/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inception_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 22:50:36 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/25 18:55:29 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	consistent_redirections(t_ast *node)
{
	int	i;

	i = 1;
	if (node)
	{
		if (0 < node->op && node->op < 4 && (!node->right || !node->right->bin))
		{
			ft_puterror(SYE"inconsistent redirection: `"BLUE, NULL);
			ft_puterror(g_sh->ops[node->op], NULL);
			ft_puterror(COLOR_E0M"'\n"E0M, NULL);
			return (0);
		}
		i *= consistent_redirections(node->left);
		i *= consistent_redirections(node->right);
	}
	return (i);
}

static t_ast	*collect_tree(t_ast *tmp, t_ast **n, int *incon)
{
	t_ast	*tree;

	tree = arrange_ast(tmp, NULL, NULL, 4);
	if (tree && !consistent_redirections(tree))
		*incon = 1;
	*n = tmp;
	if (tree)
		*n = tree;
	while (tmp && tmp->op != 4)
		tmp = tmp->next;
	return (tmp);
}

static t_ast	*append_tree(t_ast **tmp, t_ast **pipe, t_ast *n)
{
	if (!*pipe && *tmp)
	{
		(*tmp)->left = n;
		if (*pipe)
			(*tmp)->right = *pipe;
		else
			*pipe = *tmp;
		return (NULL);
	}
	else if (*pipe)
	{
		(*pipe)->right = n;
		if (*tmp)
		{
			(*tmp)->left = *pipe;
			*pipe = *tmp;
		}
		return (NULL);
	}
	return (n);
}

t_ast	*construct_tree(t_ast **head, t_ast *pipe, t_ast *n, int incon)
{
	t_ast	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->op != 4)
		{
			incon = 0;
			tmp = collect_tree(tmp, &n, &incon);
			if (incon)
				return (NULL);
			n = append_tree(&tmp, &pipe, n);
			if (n)
				return (n);
		}
		else if (tmp == *head)
			return (ft_puterror(SYE"inconsistent pipe: `"BLUE"|"E0M"'\n", NULL));
		if (tmp)
			tmp = tmp->next;
		if (tmp && tmp->op == 4)
			return (ft_puterror(SYE"inconsistent pipe: `"BLUE"|"E0M"'\n", NULL));
	}
	if (!pipe->left || !pipe->right)
		return (ft_puterror(SYE"inconsistent pipe: `"BLUE"|"E0M"'\n", NULL));
	return (pipe);
}
