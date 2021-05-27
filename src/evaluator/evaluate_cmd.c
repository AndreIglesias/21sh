/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:09:10 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/27 18:59:03 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	evaluate_builtin(t_ast *op)
{
	if (!ft_strcmp(op->bin, "echo"))
		sh_echo(op->ac, op->av);// verify flag
	else if (!ft_strcmp(op->bin, "cd"))
		sh_cd(op->ac, op->av);//check cd
	else if (!ft_strcmp(op->bin, "pwd"))
		sh_pwd();
	else if (!ft_strcmp(op->bin, "export"))
		sh_export(op->ac, op->av);//check values
	else if (!ft_strcmp(op->bin, "unset"))
		sh_unset(op->ac, op->av);//check if av right
	else if (!ft_strcmp(op->bin, "env"))
		sh_env();
	else if (!ft_strcmp(op->bin, "exit"))
		sh_exit(op->av[1]);
	else if (!ft_strcmp(op->bin, "history"))
		sh_history();
}
