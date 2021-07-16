/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <jiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:09:10 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/03 21:57:25 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	extract_file(t_ast *tmp, int fdpip)
{
	int		fd;
	char	buf;

	while (tmp)
	{
		fd = open(tmp->right->bin, O_RDONLY);
		if (fd > 0)
			while (read(fd, &buf, 1))
				write(fdpip, &buf, 1);
		close(fd);
		tmp = tmp->left;
	}
	sh_exit(NULL);
}

void	evaluate_builtin(t_ast *op)
{
	if (!ft_strcmp(op->bin, "echo"))
		sh_echo(op->ac, op->av);
	else if (!ft_strcmp(op->bin, "cd"))
		sh_cd(op->ac, op->av);
	else if (!ft_strcmp(op->bin, "pwd"))
		sh_pwd();
	else if (!ft_strcmp(op->bin, "export") || !ft_strcmp(op->bin, "setenv"))
		sh_export(op->ac, op->av);
	else if (!ft_strcmp(op->bin, "unset") || !ft_strcmp(op->bin, "unsetenv"))
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
