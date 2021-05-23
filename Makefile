#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:00:07 by ciglesia          #+#    #+#              #
#    Updated: 2021/05/23 19:48:22 by ciglesia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	minishell

#****************** INC *******************#
# General
INC			=	./include/

# Libft
SUB_MAKE	=	./libft/
INCFT		=	./libft/

INCLUDE		=	-O3 -I $(INCFT) -I $(INC)

INC_LIB		=	-L$(INCFT) -lft -lcurses


#***************** SRC* *******************#

DIRSRC		=	./src/
DIRSIG		=	$(DIRSRC)/signal_handler/
DIRTRM		=	$(DIRSRC)/terminal/
DIRANA		=	$(DIRSRC)/analizer/
DIREVL		=	$(DIRSRC)/evaluator/
DIRHIS		=	$(DIRSRC)/history/
DIRBIN		=	$(DIRSRC)/builtin/

DIRS		=	$(DIRSRC) $(DIRSIG) $(DIRTRM) $(DIRANA) $(DIREVL) $(DIRHIS) $(DIRBIN)

SRC			=	main.c
SIGNAL		=	signals.c
TERM		=	terminal.c environment.c getcmd.c keys_events.c prompt.c
HISTORY		=	load_history.c free_history.c browse_history.c
BUILTIN		=	sh_exit.c sh_pwd.c sh_echo.c sh_export.c sh_cd.c sh_env.c sh_history.c
ANALIZE		=	analizer.c ast.c lexer.c parser.c get_envar.c print_syntax.c construct_ast.c
EVAL		=	sh_which.c

SRCS		=	$(SRC) $(SIGNAL) $(TERM) $(HISTORY) $(BUILTIN) $(EVAL) $(ANALIZE)

#***************** DEPS ******************#

DIROBJ		=	./depo/

OAUX		=	$(SRCS:%=$(DIROBJ)%)
DEPS		=	$(OAUX:.c=.d)
OBJS		=	$(OAUX:.c=.o)

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -ansi -pedantic -g
	endif
else
CFLAGS		=	-Wall -Wextra -Werror
endif

CC			=	/usr/bin/clang
RM			=	/bin/rm -f
ECHO		=	/bin/echo -e
BOLD		=	"\e[1m"
BLINK		=	 "\e[5m"
RED			=	 "\e[38;2;255;0;0m"
GREEN		=	 "\e[92m"
BLUE		=	 "\e[34m"
YELLOW		=	 "\e[33m"
E0M			=	 "\e[0m"

#************************ DEPS COMPILATION *************************

%.o		:		../$(DIRSRC)/%.c
				@printf $(GREEN)"Generating minishell objects... %-33.33s\r" $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRSIG)/%.c
				@printf $(GREEN)"Generating minishell objects... %-33.33s\r" $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRTRM)/%.c
				@printf $(GREEN)"Generating minishell objects... %-33.33s\r" $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRHIS)/%.c
				@printf $(GREEN)"Generating minishell objects... %-33.33s\r" $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRBIN)/%.c
				@printf $(GREEN)"Generating minishell objects... %-33.33s\r" $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRANA)/%.c
				@printf $(GREEN)"Generating minishell objects... %-33.33s\r" $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIREVL)/%.c
				@printf $(GREEN)"Generating minishell objects... %-33.33s\r" $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

#************************ MAIN COMPILATION *************************

$(NAME)	:		ftlib $(OBJS)
				@printf $(E0M)"\n"
				@$(CC)  $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS) $(INC_LIB)
				@$(ECHO) $(RED) $(BOLD)
				@$(ECHO) '              ,---------------------------,'
				@$(ECHO) '              |  /---------------------\  |'
				@$(ECHO) '              | |  '$(GREEN)'    I GIVE YOU  '$(RED)'     | |'
				@$(ECHO) '              | |  '$(GREEN)'   My beautiful '$(RED)'     | |'
				@$(ECHO) '              | |  '$(GREEN)'    minishell   '$(RED)'     | |'
				@$(ECHO) '              | |  '$(GREEN)$(BLINK)'       C:\>     '$(E0M)$(BOLD)$(RED)'     | |'
				@$(ECHO) '              | |                       | |'
				@$(ECHO) '              |  \_____________________/  |'
				@$(ECHO) '              |___________________________|'
				@$(ECHO) '            ,---\_____     []     _______/------,'
				@$(ECHO) '          /         /______________\           /|'
				@$(ECHO) '        /___________________________________ /  | ___'
				@$(ECHO) '        |                                   |   |    )'
				@$(ECHO) '        |  _ _ _                 [-------]  |   |   ('
				@$(ECHO) '        |  o o o                 [-------]  |  /    _)_'
				@$(ECHO) '        |__________________________________ |/     /  /'
				@$(ECHO) '    /-------------------------------------/|      ( )/'
				@$(ECHO) '  /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ /'
				@$(ECHO) '/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ /'
				@$(ECHO) '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
				@$(ECHO) $(E0M)
				@$(ECHO) $(BOLD)$(GREEN)'> Compiled'$(E0M)

clean	:
				@($(RM) $(OBJS))
				@($(RM) $(DEPS))
				@(cd $(SUB_MAKE) && $(MAKE) clean)
				@$(ECHO) $(RED)'> Directory cleaned'$(E0M)

all		:		$(NAME)

fclean	:		clean
				@$(RM) $(NAME)
				@(cd $(SUB_MAKE) && $(MAKE) fclean)
				@$(ECHO) $(RED)'> Executable removed'$(E0M)

re		:		fclean all

ftlib	:
				@(cd $(SUB_MAKE) && $(MAKE))

.PHONY	:		all clean re

-include $(DEPS)
