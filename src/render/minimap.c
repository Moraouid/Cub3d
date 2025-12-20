/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 23:23:02 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/20 18:07:36 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_pixel_color(t_img *img, int x, int y)
{
	char	*pixel_addr;

	if (x < 0 || y < 0)
		return (0);
	pixel_addr = img->addr + (y * img->line_length + x * (img->bits_per_pixel
				/ 8));
	return (*(int *)pixel_addr);
}

void	draw_circle(t_game *game, float x, float y, float radius)
{
	float	dy;
	float	dx;

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

void	draw_square(t_game *game, float x, float y, int color)
{
	int	j;
	int	i;

	j = 0;
	while (j < (T_SIZE * game->sf))
	{
		i = 0;
		while (i < (T_SIZE * game->sf))
		{
			my_mlx_pixel_put(&game->img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_ray(t_game *game, float angle, int length)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	while (i < length)
	{
		x = game->player.x + cos(angle) * i;
		y = game->player.y + sin(angle) * i;
		if (x < 0 || y < 0)
			break ;
		my_mlx_pixel_put(&game->img, game->sf * x + 10, game->sf * y + 10, RED);
		i++;
	}
}

void	render_mini_map(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	game->sf = 0.2;
	while (game->map.height * T_SIZE * game->sf > WINDOW_H / 3)
		game->sf -= 0.001;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
		{
			c = game->map.map[i][j];
			if (c == '1')
				draw_square(game, game->sf * T_SIZE * j + 10, game->sf * T_SIZE
					* i + 10, GRAY);
			else if (c == '0' || c == 'E' || c == 'S' || c == 'N' || c == 'W')
				draw_square(game, game->sf * T_SIZE * j + 10, game->sf * T_SIZE
					* i + 10, WHITE);
		}
	}
	draw_ray(game, game->player.angle, 30);
	draw_circle(game, game->sf * game->player.x + 10, game->sf * game->player.y
		+ 10, 2);
}
