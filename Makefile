NAME = cub3D
CC = cc -g
MLX = -L/usr/include/minilibx-linux -lmlx -lXext -lX11 -lm
GNL = includes/get_next_line/get_next_line.c includes/get_next_line/get_next_line_utils.c 
CFLAGS = -Wall -Wextra -Werror
SRCS = src/cub3d.c src/start_game.c src/parsing/init_var.c src/parsing/parse_colors.c \
		src/parsing/parse_map.c src/parsing/utils.c src/parsing/validate_map.c src/helper/ft_atoi.c \
		src/parsing/parse_map_helper.c src/helper/ft_split.c src/helper/ft_strdup.c src/helper/ft_strlen.c \
		src/helper/ft_substr.c src/helper/gc.c src/render/minimap.c src/render/my_mlx_pixel_put.c src/render/window.c \
		src/render/raycasting_helper.c src/render/movement.c src/render/raycasting.c src/render/render_wall.c src/helper/ft_memset.c

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
