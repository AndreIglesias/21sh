/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 07:13:31 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/16 16:19:00 by ciglesia         ###   ########.fr       */
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

static void	keys_transmit(t_events *event)
{
	static char	up[] = {27, 91, 65, 0};
	static char	dw[] = {27, 91, 66, 0};
	static char	rg[] = {27, 91, 67, 0};
	static char	lf[] = {27, 91, 68, 0};

	event->up = up;
	event->dw = dw;
	event->rg = rg;
	event->lf = lf;
	event->sc = tgetstr("sc", NULL);
	event->rc = tgetstr("rc", NULL);
	event->dc = tgetstr("dc", NULL);
	event->ce = tgetstr("ce", NULL);
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
	if (!event)
		return (NULL);
	event->ks = tgetstr("ks", NULL);
	if (!event->ks)
	{
		free(event);
		return (ft_puterror(MINERR"Could not turn keypad on.\n"E0M, 0));
	}
	keys_transmit(event);
	return (event);
}

static void	init_termios(t_shell *sh)
{
	(void)sh;
	tcgetattr(0, &(sh->old_term));
	tcgetattr(0, &(sh->new_term));
	sh->new_term.c_lflag &= ~(ICANON);
	sh->new_term.c_lflag &= ~(ECHO);
	sh->new_term.c_cc[VMIN] = 1;
	sh->new_term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &(sh->new_term));
}

t_shell	*ft_shell(void)
{
	t_shell	*sh;

	sh = malloc(sizeof(t_shell));
	if (!sh)
		return (NULL);
	init_termios(sh);
	sh->events = init_termcap();
	if (!sh->events)
		return (NULL);
	sh->ev = NULL;
	sh->line = NULL;
	return (sh);
}
