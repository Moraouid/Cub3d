/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:35:05 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/20 21:25:49 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	game_update(t_game *game)
{
	int	c_floor;
	int	c_ceiling;

	c_floor = (game->floor.r << 16) | (game->floor.g << 8) | game->floor.b;
	c_ceiling = (game->ceil.r << 16) | (game->ceil.g << 8) | game->ceil.b;
	ceiling_and_floor(game, c_ceiling, c_floor);
	raycasting(game);
	render_mini_map(game);
	move_player(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->img.img, 0, 0);
	return (0);
}

void	init_player(t_player *player, int x, int y, float angle)
{
	player->x = x + T_SIZE / 2;
	player->y = y + T_SIZE / 2;
	player->angle = angle;
}

void	set_player_orientation(t_game *game, int x, int y, char c)
{
	if (c == 'N')
		init_player(&game->player, x, y, 3 * M_PI_2);
	else if (c == 'S')
		init_player(&game->player, x, y, M_PI_2);
	else if (c == 'E')
		init_player(&game->player, x, y, 0);
	else if (c == 'W')
		init_player(&game->player, x, y, M_PI);
}

void	set_player(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			c = game->map.map[i][j];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				set_player_orientation(game, j * T_SIZE, i * T_SIZE, c);
			j++;
		}
		i++;
	}
}

void	start_game(t_game *game)
{
	game->mlx.mlx = mlx_init();
	init_img(game);
	load_texture(game, &game->south, game->tex.so_path);
	load_texture(game, &game->north, game->tex.no_path);
	load_texture(game, &game->east, game->tex.ea_path);
	load_texture(game, &game->west, game->tex.we_path);
	set_player(game);
	game->mlx.win = mlx_new_window(game->mlx.mlx, WINDOW_W, WINDOW_H, "CUB3D");
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win, 3, 1L << 1, release_key_press, game);
	mlx_hook(game->mlx.win, 17, 0, my_exit, game);
	mlx_loop_hook(game->mlx.mlx, game_update, game);
	mlx_loop(game->mlx.mlx);
}
