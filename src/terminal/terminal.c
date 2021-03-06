/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 19:16:58 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/21 14:43:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** ESC[<letter>\0
** up ^[[A
** dw ^[[B
** rg ^[[C
** lf ^[[D
** Keypad Section:
** `ks' Turn keypad keys transmit
** Cursor motion Section:
** `sc' Makes the terminal save the current cursor position
** `rc' Makes the terminal save the restore the last saved cursor position
** Insert/Delete Character Section:
** `dc' Deletes on character position at the cursor
** Clearing Parts of the Screen Section:
** `ce' Clears from the cursor to the end of the current line
*/

static int	keys_transmit(t_events *event)
{
	static char	up[] = {27, 91, 65, 0};
	static char	dw[] = {27, 91, 66, 0};
	static char	rg[] = {27, 91, 67, 0};
	static char	lf[] = {27, 91, 68, 0};

	event->ks = tgetstr("ks", NULL);
	if (!event->ks)
	{
		free(event);
		return ((int)ft_puterror(MINERR"Could not turn keypad on.\n"E0M, 0));
	}
	event->up = up;
	event->dw = dw;
	event->rg = rg;
	event->lf = lf;
	event->sc = tgetstr("sc", NULL);
	event->rc = tgetstr("rc", NULL);
	event->dc = tgetstr("dc", NULL);
	event->ce = tgetstr("ce", NULL);
	return (1);
}

t_events	*init_termcap(void)
{
	t_events	*event;
	char		*termtype;
	int			connect;

	termtype = getenv("TERM");
	if (!termtype)
		return (ft_puterror(MINERR"Specify a terminal type with the \
environmental variable TERM.\n"E0M, 0));
	connect = tgetent(NULL, termtype);
	if (connect < 0)
		return (ft_puterror(MINERR"Could not access the termcap DB.\n"E0M, 0));
	else if (connect == 0)
		return (ft_puterror(MINERR"Terminal type is not defined.\n"E0M, 0));
	event = malloc(sizeof(t_events));
	if (!event || !keys_transmit(event))
		return (NULL);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &event->ws);
	return (event);
}

static void	init_termios(t_shell *sh)
{
	tcgetattr(0, &(sh->old_term));
	tcgetattr(0, &(sh->new_term));
	sh->new_term.c_lflag &= ~(ICANON | ECHO);
	sh->new_term.c_cc[VMIN] = 1;
	sh->new_term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &(sh->new_term));
}

t_shell	*ft_shell(void)
{
	static char	*ops[] = {NULL, "<", ">", ">>", "|"};
	t_shell		*sh;

	sh = malloc(sizeof(t_shell));
	if (!sh)
		return (NULL);
	init_termios(sh);
	sh->events = init_termcap();
	if (!sh->events)
		return (NULL);
	sh->ev = NULL;
	sh->history = NULL;
	sh->history_path = NULL;
	sh->history_cursor = NULL;
	sh->cmds = NULL;
	sh->cmd_line = NULL;
	sh->ncmd = 1;
	sh->last_status = 0;
	sh->envp = NULL;
	sh->ops = ops;
	sh->syntax = SYNTAX;
	sh->pid = NULL;
	return (sh);
}
