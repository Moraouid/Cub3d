NAME = cub3d
CC = cc
MLX = -L/usr/include/minilibx-linux -lmlx -lXext -lX11 
GNL = includes/get_next_line/get_next_line.c includes/get_next_line/get_next_line_utils.c 
CFLAGS = -Wall -Wextra -Werror
SRCS = $(wildcard src/parsing/*.c)

OBJS = $(SRCS:.c=.o)

all: printf $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(GNL) 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re  
