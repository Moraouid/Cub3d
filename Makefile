NAME = cub3d
CC = cc -g
MLX = -L/usr/include/minilibx-linux -lmlx -lXext -lX11 -lm
GNL = includes/get_next_line/get_next_line.c includes/get_next_line/get_next_line_utils.c 
CFLAGS = -Wall -Wextra -Werror
SRCS = src/cub3d.c src/start_game.c $(wildcard src/parsing/*.c) $(wildcard ./src/helper/*.c) \
		$(wildcard src/render/*.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(GNL)


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
