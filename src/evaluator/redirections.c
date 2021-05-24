/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:01:18 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/22 22:32:48 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	redirect_builtin(t_ast *op)
{
}

void	redirections(t_ast *op)
{
	if(is_builtin(op->left->bin))
		redirect_builtin(op);
	else
	{
		if (op->op == 1)
			stdin_to_bin(op);
		if (op->left->op == 2)
			bin_stdout_to_file(op);
		if (op->left->op == 3)
			bin_stdout_to_eof(op);
		if (op->left->op == 4)
			stdout_to_bin(op);
	}
}
