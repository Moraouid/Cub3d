/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 23:57:29 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/19 11:43:43 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	cant_move_forward_backward(t_game *game, char key)
{
	float	x;
	float	y;

	if (key == 'w')
	{
		corner_of_player(game, game->player.angle, 1);
		x = game->player.x + cos(game->player.angle) * SPEED;
		y = game->player.y + sin(game->player.angle) * SPEED;
		if (!check_wall(game, x, y))
			return (0);
	}
	if (key == 's')
	{
		corner_of_player(game, game->player.angle, 0);
		x = game->player.x - cos(game->player.angle) * SPEED;
		y = game->player.y - sin(game->player.angle) * SPEED;
		if (!check_wall(game, x, y))
			return (0);
	}
	return (1);
}

int	cant_move_sidewalk(t_game *game, char key)
{
	float	x;
	float	y;

	if (key == 'a')
	{
		corner_of_player(game, game->player.angle - M_PI_2, 1);
		x = game->player.x + cos(game->player.angle - M_PI_2) * SPEED;
		y = game->player.y + sin(game->player.angle - M_PI_2) * SPEED;
		if (!check_wall(game, x, y))
			return (0);
	}
	if (key == 'd')
	{
		corner_of_player(game, game->player.angle + M_PI_2, 1);
		x = game->player.x + cos(game->player.angle + M_PI_2) * SPEED;
		y = game->player.y + sin(game->player.angle + M_PI_2) * SPEED;
		if (!check_wall(game, x, y))
			return (0);
	}
	return (1);
}

int	move_player(t_game *game)
{
	if (game->keymove.w == 1 && !cant_move_forward_backward(game, 'w'))
	{
		game->player.x += cos(game->player.angle) * SPEED;
		game->player.y += sin(game->player.angle) * SPEED;
	}
	if (game->keymove.s == 1 && !cant_move_forward_backward(game, 's'))
	{
		game->player.x -= cos(game->player.angle) * SPEED;
		game->player.y -= sin(game->player.angle) * SPEED;
	}
	if (game->keymove.a == 1 && !cant_move_sidewalk(game, 'a'))
	{
		game->player.x += cos(game->player.angle - M_PI_2) * SPEED;
		game->player.y += sin(game->player.angle - M_PI_2) * SPEED;
	}
	if (game->keymove.d == 1 && !cant_move_sidewalk(game, 'd'))
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
		my_exit(game);
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
