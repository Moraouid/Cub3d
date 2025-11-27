/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 23:23:45 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/11/27 07:44:36 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	height_and_width(t_game *game)
{
	int	h;
	int	w;
	int	i;

	h = 0;
	while (game->map.map[h])
		h++;
	game->map.height = h;
	i = 0;
	w = 0;
	while (i < h)
	{
		if (ft_strlen(game->map.map[i]) > w)
			w = ft_strlen(game->map.map[i]);
		i++;
	}
	game->map.width = w;
}

int	is_wall(t_game *game, float x, float y)
{
	int	dx;
	int	dy;

	dx = (int)(x / T_SIZE);
	dy = (int)(y / T_SIZE);
	if (y < 0 || x < 0 || y >= game->map.height || x >= game->map.width)
		return (1);
	if (x >= ft_strlen(game->map.map[dy]))
		return (1);
	if (game->map.map[dy][dx] == '1')
		return (1);
	return (0);
}

int	extract_color(char *color)
{
	int	n_color;

	n_color = atoi(color);
	if (n_color >= 0 && n_color <= 255)
		return (n_color);
	else
		return (-1);
}

void	parse_color(char *line, t_color *color, t_gc *gc)
{
	char	**rgb;
	int		i;

	i = 1;
	while (line[i] == ' ')
		i++;
	if (!line)
	{
		printf("Error_color1\n");
		exit(1);
	}
	rgb = ft_split(line, ',', &gc);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		printf("Error_color2\n");
		exit(1);
	}
	color->r = extract_color(rgb[0]);
	color->g = extract_color(rgb[1]);
	color->b = extract_color(rgb[2]);
	if (color->r == -1 || color->g == -1 || color->b == -1)
	{
		printf("Error_color3\n");
		exit(1);
	}
}

int	is_chars_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	parse_map(t_game *game, int fd, char *line)
{
	char	*temp;

	int i, len;
	i = 0;
	game->map.map = malloc(sizeof(char *) * 2048);
	if (!game->map.map)
		exit(1);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		write(2, "Error: Empty map\n", 17);
		exit(1);
	}
	while (line)
	{
		if (line[0] == '\n')
			break ;
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			len--;
		temp = ft_substr(line, 0, len);
		if (!is_chars_valid(temp))
		{
			write(2, "Error: Invalid character in map\n", 33);
			exit(1);
		}
		game->map.map[i++] = temp;
		free(line);
		line = get_next_line(fd);
	}
	game->map.map[i] = NULL;
}

char	*init_var(t_game *game, char *line, int fd)
{
	int	i;

	i = 0;
	while (line)
	{
		if (*line == '\n' && i < 6)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!strncmp(line, "NO ", 3) && !game->tex.no_path)
			game->tex.no_path = ft_substr(line, 3, ft_strlen(line) - 4);
		else if (!strncmp(line, "SO ", 3) && !game->tex.so_path)
			game->tex.so_path = ft_substr(line, 3, ft_strlen(line) - 4);
		else if (!strncmp(line, "WE ", 3) && !game->tex.we_path)
			game->tex.we_path = ft_substr(line, 3, ft_strlen(line) - 4);
		else if (!strncmp(line, "EA ", 3) && !game->tex.ea_path)
			game->tex.ea_path = ft_substr(line, 3, ft_strlen(line) - 4);
		else if (!strncmp(line, "F ", 2))
			parse_color(ft_substr(line, 2, ft_strlen(line) - 3), &game->floor,
				game->gc);
		else if (!strncmp(line, "C ", 2))
			parse_color(ft_substr(line, 2, ft_strlen(line) - 3), &game->ceiling,
				game->gc);
		else
			return (line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (line);
}

void	parse_file(int fd, t_game *game)
{
	char	*line;
	char	*map_line;

	line = get_next_line(fd);
	map_line = init_var(game, line, fd);
	if (game->tex.no_path && game->tex.so_path && game->tex.we_path
		&& game->tex.ea_path)
	{
		if (map_line)
			parse_map(game, fd, map_line);
		else
		{
			printf("Error: No map found\n");
			exit(1);
		}
	}
	else
	{
		free(map_line);
		printf("Error: invalid path or less/more texture \n");
		exit(1);
	}
}

int	my_exit(void)
{
	exit(1);
	return (0);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	in_map(t_game *game, int mi, int mj)
{
	if (mi < 0 || mj < 0)
		return (0);
	if (!game->map.map[mi])
		return (0);
	if (!game->map.map[mi][mj])
		return (0);
	return (1);
}

// float	cast_ray(t_game *game, float angle)
// {
// 	int		hit;
// 	t_dda	dda;
// 	float	r_dirx;
// 	float	r_diry;
// 	float	dis;

// 	hit = 0;
// 	// deriction of player
// 	r_dirx = cos(angle);
// 	r_diry = sin(angle);
// 	//
// 	dda.x_map = (int)(game->player.x / T_SIZE);
// 	dda.y_map = (int)(game->player.y / T_SIZE);
// 	//
// 	if (r_dirx == 0)
// 		dda.d_distx = WINDOW_W;
// 	else
// 		dda.d_distx = fabs(1 / r_dirx);
// 	if (r_diry == 0)
// 		dda.d_disty = WINDOW_W;
// 	else
// 		dda.d_disty = fabs(1 / r_diry);
// 	if (r_dirx < 0)
// 	{
// 		dda.x_step = -1;
// 		dda.s_distx = (game->player.x / T_SIZE - dda.x_map) * dda.d_distx;
// 	}
// 	else
// 	{
// 		dda.x_step = 1;
// 		dda.s_distx = (dda.x_map + 1.0 - game->player.x / T_SIZE) * dda.d_distx;
// 	}
// 	if (r_diry < 0)
// 	{
// 		dda.y_step = -1;
// 		dda.s_disty = (game->player.y / T_SIZE - dda.y_map) * dda.d_disty;
// 	}
// 	else
// 	{
// 		dda.y_step = 1;
// 		dda.s_disty = (dda.y_map + 1.0 - game->player.y / T_SIZE) * dda.d_disty;
// 	}
// 	while (!hit)
// 	{
// 		if (dda.s_distx < dda.s_disty)
// 		{
// 			dda.s_distx += dda.d_distx;
// 			dda.x_map += dda.x_step;
// 			dda.side = 0;
// 		}
// 		else
// 		{
// 			dda.s_disty += dda.d_disty;
// 			dda.y_map += dda.y_step;
// 			dda.side = 1;
// 		}
// 		if (is_wall(game, dda.x_map, dda.y_map))
// 			hit = 1;
// 	}
// 	if (dda.side == 0)
// 		dis = dda.s_distx - dda.d_distx;
// 	else
// 		dis = dda.s_disty - dda.d_disty;
// 	return (dis);
// }

void	draw_circle(t_game *game, int x, int y, int radius)
{
	int	dy;
	int	dx;

	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
				my_mlx_pixel_put(&game->img, x + dx, y + dy, RED);
			dx++;
		}
		dy++;
	}
}

void	draw_square(t_game *game, int x, int y, int size, int color)
{
	int	j;
	int	i;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			my_mlx_pixel_put(&game->img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	init_player(t_player *player, int x, int y, float angle)
{
	if (!player->flag)
	{
		player->x = x + 8;
		player->y = y + 8;
		player->angle = angle;
		player->flag = 1;
	}
}

void	render_mini_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == '1')
				draw_square(game, j * T_SIZE, i * T_SIZE, T_SIZE, GRAY);
			else if (game->map.map[i][j] == '0')
				draw_square(game, j * T_SIZE, i * T_SIZE, T_SIZE, WHITE);
			else if (game->map.map[i][j] == 'N')
			{
				draw_square(game, j * T_SIZE, i * T_SIZE, T_SIZE, WHITE);
				init_player(&game->player, j * T_SIZE, i * T_SIZE, 3 * M_PI_2);
			}
			else if (game->map.map[i][j] == 'S')
			{
				draw_square(game, j * T_SIZE, i * T_SIZE, T_SIZE, WHITE);
				init_player(&game->player, j * T_SIZE, i * T_SIZE, M_PI_2);
			}
			else if (game->map.map[i][j] == 'E')
			{
				draw_square(game, j * T_SIZE, i * T_SIZE, T_SIZE, WHITE);
				init_player(&game->player, j * T_SIZE, i * T_SIZE, 0);
			}
			else if (game->map.map[i][j] == 'W')
			{
				draw_square(game, j * T_SIZE, i * T_SIZE, T_SIZE, WHITE);
				init_player(&game->player, j * T_SIZE, i * T_SIZE, M_PI);
			}
			j++;
		}
		i++;
	}
	draw_circle(game, (int)game->player.x, (int)game->player.y, 3);
}

void	init_img(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx.mlx, WINDOW_W, WINDOW_H);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
}

int	cant_move(t_game *game, char key)
{
	float	x;
	float	y;

	if (key == 'w')
	{
		x = game->player.x + cos(game->player.angle) * SPEED;
		y = game->player.y + sin(game->player.angle) * SPEED;
	}
	if (key == 's')
	{
		x = game->player.x - cos(game->player.angle) * SPEED;
		y = game->player.y - sin(game->player.angle) * SPEED;
	}
	if (key == 'a')
	{
		x = game->player.x + cos(game->player.angle - M_PI_2) * SPEED;
		y = game->player.y + sin(game->player.angle - M_PI_2) * SPEED;
	}
	if (key == 'd')
	{
		x = game->player.x + cos(game->player.angle + M_PI_2) * SPEED;
		y = game->player.y + sin(game->player.angle + M_PI_2) * SPEED;
	}
	return (is_wall(game, x, y));
}

int	move_player(t_game *game)
{
	if (game->keymove.w == 1 && !cant_move(game, 'w'))
	{
		game->player.x += cos(game->player.angle) * SPEED;
		game->player.y += sin(game->player.angle) * SPEED;
	}
	if (game->keymove.s == 1 && !cant_move(game, 's'))
	{
		game->player.x -= cos(game->player.angle) * SPEED;
		game->player.y -= sin(game->player.angle) * SPEED;
	}
	if (game->keymove.a == 1 && !cant_move(game, 'a'))
	{
		game->player.x += cos(game->player.angle - M_PI_2) * SPEED;
		game->player.y += sin(game->player.angle - M_PI_2) * SPEED;
	}
	if (game->keymove.d == 1 && !cant_move(game, 'd'))
	{
		game->player.x += cos(game->player.angle + M_PI_2) * SPEED;
		game->player.y += sin(game->player.angle + M_PI_2) * SPEED;
	}
	if (game->keymove.right == 1)
		game->player.angle -= 0.01;
	if (game->keymove.left == 1)
		game->player.angle += 0.01;
	return (0);
}

int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_W)
		game->keymove.w = 1;
	if (key == KEY_S)
		game->keymove.s = 1;
	if (key == KEY_A)
		game->keymove.a = 1;
	if (key == KEY_D)
		game->keymove.d = 1;
	if (key == KEY_RIGHT)
		game->keymove.right = 1;
	if (key == KEY_LEFT)
		game->keymove.left = 1;
	return (0);
}

int	release_key_press(int key, t_game *game)
{
	if (key == KEY_W)
		game->keymove.w = 0;
	if (key == KEY_S)
		game->keymove.s = 0;
	if (key == KEY_A)
		game->keymove.a = 0;
	if (key == KEY_D)
		game->keymove.d = 0;
	if (key == KEY_RIGHT)
		game->keymove.right = 0;
	if (key == KEY_LEFT)
		game->keymove.left = 0;
	return (0);
}

void	render(t_game *game, float px, float py, float angle)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	while (i < 50)
	{
		x = px + cos(angle) * i;
		y = py + sin(angle) * i;
		if (x != game->hori.hit_x && y != game->hori.hit_y)
			my_mlx_pixel_put(&game->img, x, y, RED);
		i++;
	}
}

void	get_facing(t_player *player)
{
	player->facing_down = (player->angle > 0 && player->angle < M_PI);
	player->facing_up = !player->facing_down;
	player->facing_right = (player->angle < M_PI_2 || player->angle > 3
			* M_PI_2);
	player->facing_left = !player->facing_right;
}

float	normalize_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = 2 * M_PI + angle;
	return (angle);
}

void	raycasting(t_game *game)
{
	int		i;
	float	ray_a;
	float	step_a;
	float	start_a;

	i = 0;
	start_a = game->player.angle - FOV / 2;
	step_a = FOV / WINDOW_W;
	while (i < WINDOW_W)
	{
		ray_a = start_a + i * step_a;
		render(game, game->player.x, game->player.y, ray_a);
		i++;
	}
}

void	render_ray(t_game *game, float hit_x, float hit_y)
{
	float	dx;
	float	dy;
	float	distance;
	int		steps;
	int		x;
	int		y;

	dx = hit_x - game->player.x;
	dy = hit_y - game->player.y;
	distance = sqrt(dx * dx + dy * dy);
	steps = (int)distance;
	for (int i = 0; i < steps; i++)
	{
		x = game->player.x + dx / steps * i;
		y = game->player.y + dy / steps * i;
		my_mlx_pixel_put(&game->img, x, y, RED);
	}
}

void	horizontal_intersect(t_game *game, t_player *p, t_intersect *hori)
{
	if (p->facing_up)
		hori->first_y = floor(p->y / T_SIZE) * T_SIZE - 1;
	else if (p->facing_down)
		hori->first_y = floor(p->y / T_SIZE) * T_SIZE + T_SIZE;
	hori->first_x = (hori->first_y - p->y) / tan(p->angle) + p->x;
	if (p->facing_up)
		hori->delta_y = -T_SIZE;
	else if (p->facing_down)
		hori->delta_y = T_SIZE;
	hori->delta_x = hori->delta_y / tan(p->angle);
	hori->next_x = hori->first_x;
	hori->next_y = hori->first_y;
	while (1)
	{
		if (is_wall(game, hori->next_x, hori->next_y))
		{
			hori->hit_x = hori->next_x;
			hori->hit_y = hori->next_y;
			break ;
		}
		hori->next_x += hori->delta_x;
		hori->next_y += hori->delta_y;
	}
}

void	vertical_intersect(t_game *game, t_player *p, t_intersect *vert)
{
	if (p->facing_right)
		vert->first_x = floor(p->x / T_SIZE) * T_SIZE + T_SIZE;
	else if (p->facing_left)
		vert->first_x = floor(p->x / T_SIZE) * T_SIZE - 1;
	vert->first_y = (vert->first_x - p->x) * tan(p->angle) + p->x;
	if (p->facing_right)
		vert->delta_x = T_SIZE;
	else if (p->facing_left)
		vert->delta_x = -T_SIZE;
	vert->delta_y = vert->delta_x * tan(p->angle);
	vert->next_x = vert->first_x;
	vert->next_y = vert->first_y;
	while (1)
	{
		if (is_wall(game, vert->next_x, vert->next_y))
		{
			vert->hit_x = vert->next_x;
			vert->hit_y = vert->next_y;
			vert->dis = sqrt((p->x - vert->hit_x) * (p->x - vert->hit_x) + (p->y
						- vert->hit_y) * (p->y - vert->hit_y));
			break ;
		}
		vert->next_x += vert->delta_x;
		vert->next_y += vert->delta_y;
	}
}

t_intersect *closest_hit(t_game *game)
{
    if (game->hori.dis < game->vert.dis)
        return &game->hori;   // horizontal hit is closer
    else
        return &game->vert;   // vertical hit is closer
}

void	raycasting(t_game *game)
{
	int			i;
	float		ray_angle;
	float		step_angle;
	float		start_angle;
	t_intersect	*hit;

	start_angle = game->player.angle - FOV / 2;
	step_angle = FOV / WINDOW_W;
	for (i = 0; i < WINDOW_W; i++)
	{
		ray_angle = normalize_angle(start_angle + i * step_angle);
		// Update facing directions for this ray
		// game->player.angle = ray_angle;
		get_facing(&game->player);
		horizontal_intersect(game, &game->player, &game->hori);
		vertical_intersect(game, &game->player, &game->vert);
		hit = closest_hit(game);
		render_ray(game, hit->hit_x, hit->hit_y);
	}
}

int	update_game(t_game *game)
{
	render_mini_map(game);
	game->player.angle = normalize_angle(game->player.angle);
	get_facing(&game->player);
	horizontal_intersect(game, &game->player, &game->hori);
	vertical_intersect(game, &game->player, &game->vert);
	raycasting(game);
	move_player(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->img.img, 0, 0);
	return (0);
}

void	ceiling_and_floor(t_game *game, int ceiling, int floor)
{
	int	middle;
	int	x;
	int	y;

	y = 0;
	middle = WINDOW_H / 2;
	while (y < middle)
	{
		x = 0;
		while (x < WINDOW_W)
			my_mlx_pixel_put(&game->img, x++, y, ceiling);
		y++;
	}
	while (y < WINDOW_H)
	{
		x = 0;
		while (x < WINDOW_W)
			my_mlx_pixel_put(&game->img, x++, y, floor);
		y++;
	}
}

void	start_game(t_game *game)
{
	int	c_floor;
	int	c_ceiling;

	game->mlx.mlx = mlx_init();
	game->mlx.win = mlx_new_window(game->mlx.mlx, 1080, 720, "CUB3D");
	init_img(game);
	c_floor = (game->floor.r << 16) | (game->floor.g << 8) | game->floor.b;
	c_ceiling = (game->ceiling.r << 16) | (game->ceiling.g << 8) | game->ceiling.b;
	ceiling_and_floor(game, c_ceiling, c_floor);
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win, 3, 1L << 1, release_key_press, game);
	mlx_hook(game->mlx.win, 17, 0, my_exit, NULL);
	mlx_loop_hook(game->mlx.mlx, update_game, game);
	mlx_loop(game->mlx.mlx);
}
int	main(int ac, char **av)
{
	t_game	*game;
	int		i;
	int		fd;

	if (ac != 2)
	{
		write(2, "Error: Usage ./cub3d path_map.cub\n", 35);
		exit(1);
	}
	i = 0;
	game = NULL;
	game = malloc(sizeof(t_game));
	while (av[1][i])
		i++;
	if (av[1][i - 1] != 'b' || av[1][i - 2] != 'u' || av[1][i - 3] != 'c'
		|| av[1][i - 4] != '.')
		return (write(2, "Error: Invalid map file\n", 24));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: map mot found\n", 21);
		exit(1);
	}
	parse_file(fd, game);
	height_and_width(game);
	memset(&game->keymove, 0, sizeof(t_keymove));
	memset(&game->hori, 0, sizeof(t_intersect));
	memset(&game->vert, 0, sizeof(t_intersect));
	memset(&game->player, 0, sizeof(t_player));
	memset(&game->ceiling, 0, sizeof(t_color));
	memset(&game->floor, 0, sizeof(t_color));
	game->tex.ea_path = NULL;
	game->tex.we_path = NULL;
	game->tex.no_path = NULL;
	game->tex.we_path = NULL;
	start_game(game);
}
