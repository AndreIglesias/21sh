/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:09:10 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/24 12:51:47 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	evaluate_builtin(t_ast *op)
{
	if (!ft_strcmp(op->bin, "echo"))
		sh_echo(op->av, 0);// verify flag
	else if (!ft_strcmp(op->bin, "cd"))
		sh_cd(g_sh->ev, *op->av);//check cd
	else if (!ft_strcmp(op->bin, "pwd"))
		sh_pwd();
	else if (!ft_strcmp(op->bin, "export"))
		sh_export(g_sh->ev, "key", "value");//check values
	else if (!ft_strcmp(op->bin, "unset"))
		sh_unset(g_sh->ev, *op->av);//check if av right
	else if (!ft_strcmp(op->bin, "env"))
		sh_env(g_sh->ev);
	else if (!ft_strcmp(op->bin, "exit"))
		sh_exit();
	else if (!ft_strcmp(op->bin, "history"))
		sh_history(g_sh->history);
}
/*
void	evaluate_bin(t_ast *op)
{
	execve(op->bin, op->av, g_sh->envp);
}
*/
