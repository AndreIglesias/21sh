/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 19:18:52 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/17 19:18:53 by ciglesia         ###   ########.fr       */
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

void	add_children(t_ast *op, t_ast *left, t_ast *right)
{
	if (!op->left && left)
		op->left = left;
	if (right)
		op->right = right;
}
