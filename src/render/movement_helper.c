/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:42:57 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/20 15:13:42 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	corner_of_player(t_game *game, float angle, int flag)
{
	if (flag)
	{
		if (cos(angle) < 0)
			game->player.corner_x = -4;
		else if (cos(angle) > 0)
			game->player.corner_x = 4;
		if (sin(angle) < 0)
			game->player.corner_y = -4;
		else if (sin(angle) > 0)
			game->player.corner_y = 4;
	}
	else
	{
		if (cos(angle) < 0)
			game->player.corner_x = 4;
		else if (cos(angle) > 0)
			game->player.corner_x = -4;
		if (sin(angle) < 0)
			game->player.corner_y = 4;
		else if (sin(angle) > 0)
			game->player.corner_y = -4;
	}
}

int	check_wall(t_game *game, float x, float y)
{
	if (!is_wall(game, x + game->player.corner_x, game->player.y
			+ game->player.corner_y))
	{
		if (!is_wall(game, game->player.x + game->player.corner_x, y
				+ game->player.corner_y))
			return (0);
	}
	return (1);
}
