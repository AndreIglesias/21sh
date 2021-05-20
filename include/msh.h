/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:04:26 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/21 01:11:43 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include "libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>

# define BOLD "\e[1m"
# define DIM "\e[2m"
# define ITALIC "\e[3m"
# define UNDERL "\e[4m"
# define BLINK "\e[5m"
# define REVER "\e[7m"
# define INVIS "\e[8m"
# define RED "\e[38;2;255;0;0m"
# define CEL "\e[38;2;114;159;207m"
# define GREEN "\e[92m"
# define CYAN "\e[96m"
# define BLUE "\e[34m"
# define YELLOW "\e[33m"
# define ERROR "\e[38;2;255;0;0m\e[1mERROR\e[0m\e[38;2;255;0;0m"
# define BLACKB "\e[40m"
# define GRAY "\e[90m"
# define E0M "\e[0m"

# define MINERR "\e[38;2;255;0;0m\e[5mminishell: "
# define HRY_SIZE 100
# define BUF_LINE 10

typedef struct stat	t_stat;

/*
** type (1, cmd) (2, op)
** op (1, <) (2, >) (3, >>) (4, |)
*/

typedef struct s_ast
{
	struct s_ast	*next;
	struct s_ast	*back;
	t_uchar			type;
	struct s_ast	*left;
	struct s_ast	*right;

	char			*bin;
	char			**av;
	int				ac;

	t_uchar			op;

}	t_ast;

typedef struct s_envar
{
	char			*key;
	char			*value;
	t_uchar			set;
	struct s_envar	*next;
}	t_envar;

typedef struct s_events
{
	char	*ks;
	char	*up;
	char	*dw;
	char	*rg;
	char	*lf;
	char	*sc;
	char	*rc;
	char	*dc;
	char	*ce;
}	t_events;

typedef struct s_history
{
	char				*cmd;
	t_uchar				writen;
	struct s_history	*back;
	struct s_history	*next;
}	t_history;

typedef struct s_shell
{
	struct termios	old_term;
	struct termios	new_term;
	char			*history_path;
	t_history		*history;
	t_history		*history_cursor;
	char			*line;
	char			*line_tmp;
	size_t			line_cursor;
	t_trie			*ev;
	t_events		*events;
	t_ast			**cmds;
}	t_shell;

extern t_shell		*g_sh;

/*
**  signal_handler
*/

void		sigint_shell(int sig);
void		sigquit_shell(int sig);
void		sigtstp_shell(int sig);

/*
**	terminal
*/

t_shell		*ft_shell(void);
void		store_envar(char **ev);
ssize_t		get_cmd(void);
int			keys_event(char *buf);
void		ft_prompt(void);
/*
**	history
*/

void		load_history(void);
void		save_cmdline(t_history **hst, char *line);
void		put_history_fd(t_history *hst, int fd);
void		free_history(t_history *hst);
int			browse_history(char *buf);

/*
**	builtins
*/

void		sh_exit(void);
int			sh_pwd(void);
int			sh_echo(char *value, t_uchar flag);
void		sh_export(t_trie *ev, char *key, char *value);
int			sh_cd(t_trie *ev, char *path);

/*
**	analizer
*/

void		ft_analizer(void);
int			ft_lexer(void);
t_ast		**new_astvec(int size);

/*
**	evaluator
*/

char		*sh_which(char *name, t_trie *ev);
int			is_builtin(char *name);

#endif
