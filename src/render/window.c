/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 23:40:36 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/14 03:21:26 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_wall(t_game *game, float x, float y)
{
	int	dx;
	int	dy;

	dx = (int)(x / T_SIZE);
	dy = (int)(y / T_SIZE);
	if (dy < 0 || dx < 0 || dy >= game->map.height || dx >= game->map.width)
		return (1);
	if (dx >= ft_strlen(game->map.map[dy]))
		return (1);
	if (game->map.map[dy][dx] == '1')
		return (1);
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
