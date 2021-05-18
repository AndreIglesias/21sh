#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 14:10:41 by jiglesia          #+#    #+#              #
#    Updated: 2021/05/18 19:58:27 by ciglesia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	libft.a
INCLUDE		=	.
SRC			=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c ft_atod.c ft_exp.c ft_putstr.c ft_putchar.c ft_puterror.c ft_putnbr.c ft_rgbtoi.c ft_sqrt.c ft_newlist.c ft_newlisti.c hotrace.c ft_strcmp.c ft_strcpy.c

OBJS		=	$(SRC:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror

CC			=	/usr/bin/gcc
RM			=	/bin/rm -f

%.o: %.c
				-@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(NAME)	:		$(OBJS)
				-@ar rc $(NAME) $(OBJS)
				ranlib $(NAME)

clean	:
				-@$(RM) $(OBJS)

all		:		$(NAME)

fclean	:		clean
				-@$(RM) $(NAME)

re		:		fclean all
