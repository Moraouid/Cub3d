NAME = cub3d
CC = cc -g
MLX = -L/usr/include/minilibx-linux -lmlx -lXext -lX11 
GNL = includes/get_next_line/get_next_line.c includes/get_next_line/get_next_line_utils.c 
CFLAGS = -Wall -Wextra -Werror
SRCS = src/cub3d.c $(wildcard src/parsing/*.c)

OBJS = $(SRCS:.c=.o)

all: libft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(GNL) 

libft:
	$(MAKE) -C ./includes/libft

clean:
	$(MAKE) -C ./includes/libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C ./includes/libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re  
