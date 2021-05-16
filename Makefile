#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/14 23:06:57 by ciglesia          #+#    #+#              #
#    Updated: 2021/05/15 21:13:20 by ciglesia         ###   ########.fr        #
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
DIRANA		=	$(DIRSRC)/analysis/
DIREVL		=	$(DIRSRC)/evaluator/

SRC			=	main.c
SIGNAL		=	signals.c
TERM		=	terminal.c environment.c

SRCS		=	$(SRC) $(SIGNAL) $(TERM)

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
DIM			=	 "\e[2m"
ITALIC		=	 "\e[3m"
UNDERL		=	 "\e[4m"
BLINK		=	 "\e[5m"
REVER		=	 "\e[7m"
INVIS		=	 "\e[8m"
RED			=	 "\e[38;2;255;0;0m"
CEL			=	 "\e[38;2;114;159;207m"
GREEN		=	 "\e[92m"
CYAN		=	 "\e[96m"
BLUE		=	 "\e[34m"
YELLOW		=	 "\e[33m"
ERROR		=	 "\e[38;2;255;0;0m\e[1mERROR\e[0m\e[38;2;255;0;0m"
BLACKB		=	 "\e[40m"
GRAY		=	 "\e[90m"
E0M			=	 "\e[0m"

#************************ DEPS COMPILATION *************************

%.o		:		../$(DIRSRC)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRSIG)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRTRM)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<


#************************ MAIN COMPILATION *************************

$(NAME)	:		ftlib $(OBJS)
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
				@$(ECHO) '> Compiled'

clean	:
				@($(RM) $(OBJS))
				@($(RM) $(DEPS))
				@(cd $(SUB_MAKE) && $(MAKE) clean)
				@$(ECHO) '> Directory cleaned'

all		:		$(NAME)

fclean	:		clean
				@$(RM) $(NAME)
				@(cd $(SUB_MAKE) && $(MAKE) fclean)
				@$(ECHO) '> Remove executable'

re		:		fclean all

ftlib	:
				@(cd $(SUB_MAKE) && $(MAKE))

.PHONY	:		all clean re

-include $(DEPS)