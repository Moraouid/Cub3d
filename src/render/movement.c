/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 23:57:29 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/11/29 21:28:02 by sel-abbo         ###   ########.fr       */
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
