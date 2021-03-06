/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:04:26 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/02 19:07:05 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# ifdef M_SYNTAX
#  define SYNTAX	1
# else
#  define SYNTAX	0
# endif

# ifdef M_LS
#  define LS	0
# else
#  define LS	1
# endif

# ifdef M_EVAL
#  define EVAL	0
# else
#  define EVAL	1
# endif

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
# include <sys/ioctl.h>

# define BOLD "\e[1m"
# define DIM "\e[2m"
# define ITALIC "\e[3m"
# define UNDERL "\e[4m"
# define BLINK "\e[5m"
# define REVER "\e[7m"
# define INVIS "\e[8m"
# define RED "\e[38;2;255;0;0m"
# define BLACK "\e[38;2;0;0;0m"
# define CEL "\e[38;2;114;159;207m"
# define GREEN "\e[92m"
# define CYAN "\e[38;5;31m"
# define BLUE "\e[34m"
# define YELLOW "\e[33m"
# define BLACKB "\e[40m"
# define GRAY "\e[38;5;236m"
# define LIGHT_GRAY "\e[90m"

# define BG_LIGHT_GRAY "\e[100m"
# define BG_CYAN "\e[48;5;31m"
# define BG_RED "\e[48;5;202m"
# define BG_GRAY "\e[48;5;236m"
# define BG_E0M "\e[49m"
# define COLOR_E0M "\e[39m"
# define E0M "\e[0m"
# define LOCK "\uE0A2"
# define ARROW "\uE0B0"
# define WORRA "\uE0B2"
# define TRIANG "\uE0B3"

# define MINERR "\e[38;2;255;0;0m\e[5mminishell: "
# define HRY_SIZE 100
# define BUF_LINE 10
# define PROMPT_LEN 4
# define SYE "\e[1mminishell: syntax error "

typedef struct s_coords
{
	long	len;
	long	ll;
	long	lc;
	long	cl;
	long	cc;
}	t_coords;

/*
** type (1, cmd) (2, op)
** op (1, <) (2, >) (3, >>) (4, |)
*/

typedef struct s_ast
{
	struct s_ast	*next;
	struct s_ast	*back;
	t_uchar			valid;
	t_uchar			type;
	struct s_ast	*left;
	struct s_ast	*right;

	char			*bin;
	char			**av;
	int				ac;

	t_uchar			op;

}	t_ast;

/*
**	termcaps
**		ks = keypad keys transmit
*/

typedef struct s_events
{
	struct winsize	ws;
	struct winsize	pws;
	char			*ks;
	char			*up;
	char			*dw;
	char			*rg;
	char			*lf;
	char			*sc;
	char			*rc;
	char			*dc;
	char			*ce;
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
	t_history		*shadow;
	size_t			prompt_x;
	size_t			prompt_y;
	char			*line;
	long			line_size;
	char			**cmd_line;
	int				ncmd;
	char			*line_tmp;
	long			line_cursor;
	t_trie			*ev;
	t_events		*events;
	t_ast			**cmds;
	char			**ops;
	int				last_status;
	t_uchar			syntax;
	char			**envp;
	t_ast			*pid;
	char			**builtins;
}	t_shell;

extern t_shell		*g_sh;

void		init_line(void);

/*
**  signal_handler
*/

void		sigint_shell(int sig);
void		sigquit_shell(int sig);
void		sigtstp_shell(int sig);
void		sig_child(int sig);

/*
**	terminal
*/

t_shell		*ft_shell(void);
void		store_envar(char **ev);
ssize_t		get_cmd(void);
int			keys_event(char *buf);
void		ft_prompt(void);
void		porcelain_prompt(char *branch);

/*
**		line_editor
*/

int			next_space(char *str, int i);
int			next_char(char *str, int i);


int			move_arrows(char *buf);
t_coords	cursor_position(void);
void		clear_line(void);

int			ctrl_l(void);
int			move_ctrl(char *buf);
int			jump_sides(char *buf);
int			move_cursor(char *buf);

int			delete_key(void);
int			revdel_key(void);
/*
**		autocomplete
*/

int			auto_complete(void);
int			path_completion(char *path, char *name);
int			complete_in_dir(char *folder, char *name, DIR *dir, size_t size);
void		history_shadow(void);
int			insert_shadow(void);
void		reset_shadow(void);

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

void		sh_exit(char *value);
void		sh_pwd(void);
void		sh_echo(int argc, char **value);
void		sh_export(int argc, char **key);
void		sh_cd(int argv, char **argc);
void		sh_env(void);
void		sh_history(void);
void		sh_unset(int argc, char **key);
int			sh_syntax(int ac, char	**av);

/*
**	analyzer
*/

int			is_bin(t_ast *node);
int			is_pipe(t_ast *node);
t_uchar		is_op(char *str);
int			ft_cspecial(const char *c);
int			ft_analyze(void);
int			end_of_token(char *str, int i, char quote);

int			ft_lexer(int x);
int			is_envar(char *s, int i);
int			envar_len(char *s, int i, int dig);
void		extract_tokens(char *str, int x);
char		*replace_envar(char *str, int *i, int type);
char		*replace_home(char *str, int *i);

int			ft_parser(int x);
t_ast		*arrange_ast(t_ast *tmp, t_ast *left, t_ast *op, t_ast *cmd);
t_ast		*construct_tree(t_ast **head, t_ast *pipe, t_ast *n, int incon);

int			ft_semantic(int x);

/*
** ast
*/

t_ast		*first_in_list(t_ast *node, t_uchar opp);
void		print_tokens(t_ast *tmp, int i, t_uchar opp);
void		print_btree(t_ast *node, char *prefix, t_uchar is_left);
t_ast		**new_astvec(int size);
void		delete_astnode(t_ast *node);
void		add_ast(t_ast **head, t_ast *node);
void		add_children(t_ast *op, t_ast *left, t_ast *right);
t_ast		*new_astcmd(char *cmd, char **av);
t_ast		*new_astop(t_uchar op);
void		free_cmd_line(void);
void		free_ast(void);

/*
**	evaluator
*/

char		*sh_which(char *name, t_trie *ev);
int			is_builtin(char *name);
void		ft_evaluate(void);
void		evaluate_redirect(t_ast *op);
int			op_or_cmds(t_ast *cmds);
void		evaluate_builtin(t_ast *op);
void		parent_fork(int sig);
void		append_create_fd(int fdpip, t_ast *op);
void		cat_last_file(t_ast *cmds);

void		sh_execv(char *name, char **av);
void		xcmd(char *cmd[]);
void		xcmd2(char *cmd[]);
char		*xbuff(char *cmd[], int nl);
int			xcmdfd(char *cmd[]);

void		stdin_to_bin(t_ast *cmds);
void		save_envp(t_trie *root, char *str, int lvl);
void		extract_file(t_ast *tmp, int fdpip);

#endif
