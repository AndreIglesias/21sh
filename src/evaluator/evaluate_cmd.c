/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:09:10 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/02 00:36:33 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	ctrl_l(void)
{
	char	**argv;
	int		pid;

	pid = fork();
	if (pid)
		parent_fork(pid);
	else
	{
		argv = str_to_arr("/usr/bin/clear", NULL);
		sh_execv(argv[0], argv);
		ft_freesplit(argv);
		sh_exit(NULL);
	}
	ft_prompt();
	return (0);
}

void	evaluate_builtin(t_ast *op)
{
	if (!ft_strcmp(op->bin, "echo"))
		sh_echo(op->ac, op->av);
	else if (!ft_strcmp(op->bin, "cd"))
		sh_cd(op->ac, op->av);
	else if (!ft_strcmp(op->bin, "pwd"))
		sh_pwd();
	else if (!ft_strcmp(op->bin, "export"))
		sh_export(op->ac, op->av);
	else if (!ft_strcmp(op->bin, "unset"))
		sh_unset(op->ac, op->av);
	else if (!ft_strcmp(op->bin, "env"))
		sh_env();
	else if (!ft_strcmp(op->bin, "exit"))
		sh_exit(op->av[1]);
	else if (!ft_strcmp(op->bin, "history"))
		sh_history();
	else if (!ft_strcmp(op->bin, "syntax"))
		sh_syntax(op->ac, op->av);
}
