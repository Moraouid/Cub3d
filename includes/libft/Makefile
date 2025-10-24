# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 11:56:22 by sel-abbo          #+#    #+#              #
#    Updated: 2024/11/08 19:38:24 by sel-abbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror
ARCH = ar rcs
RM = rm -f

FILES = ft_atoi.c ft_itoa.c ft_putnbr_fd.c ft_strlen.c ft_toupper.c ft_bzero.c \
		ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_calloc.c ft_memcmp.c \
		ft_split.c ft_strncmp.c ft_isalnum.c ft_memcpy.c ft_strchr.c \
		ft_strnstr.c ft_isalpha.c ft_memmove.c ft_strdup.c ft_strrchr.c \
		ft_isascii.c ft_memset.c ft_strtrim.c ft_isdigit.c \
		ft_putchar_fd.c ft_strlcat.c ft_substr.c ft_isprint.c  ft_putendl_fd.c \
		ft_strlcpy.c ft_tolower.c ft_striteri.c

OB = ${FILES:.c=.o}

%.o:%.c
	${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OB}
	${ARCH} ${NAME} ${OB}

all: ${NAME}

clean:
	${RM} ${OB} 

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
