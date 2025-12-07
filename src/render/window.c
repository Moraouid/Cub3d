/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 23:40:36 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/11/29 21:27:40 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
