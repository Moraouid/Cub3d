/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:17:24 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/18 12:03:24 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	normalize_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle <= 0)
		angle = 2 * M_PI + angle;
	return (angle);
}

void	get_facing(t_ray *ray, float angle)
{
	ray->facing_down = (angle > 0 && angle < M_PI);
	ray->facing_up = !ray->facing_down;
	ray->facing_right = (angle < M_PI_2 || angle > 3 * M_PI_2);
	ray->facing_left = !ray->facing_right;
}

void	hit_wall(t_game *game, t_intersect *inter)
{
	float	max_x;
	float	max_y;

	max_x = (float)(game->map.width * T_SIZE);
	max_y = (float)(game->map.height * T_SIZE);
	while (inter->next_x >= 0.0f && inter->next_x < max_x
		&& inter->next_y >= 0.0f && inter->next_y < max_y)
	{
		if (is_wall(game, inter->next_x, inter->next_y))
		{
			inter->hit_x = inter->next_x;
			inter->hit_y = inter->next_y;
			inter->hit = 1;
			break ;
		}
		inter->next_x += inter->delta_x;
		inter->next_y += inter->delta_y;
	}
}

void	calculate_distances(t_intersect *hori, t_intersect *vert, t_game *game)
{
	hori->dis = 1e30;
	vert->dis = 1e30;
	if (hori->hit)
		hori->dis = hypot(hori->hit_x - game->player.x, hori->hit_y
				- game->player.y);
	if (vert->hit)
		vert->dis = hypot(vert->hit_x - game->player.x, vert->hit_y
				- game->player.y);
}

void	dist_calcule(t_game *game, t_ray *ray)
{
	t_intersect	hori;
	t_intersect	vert;

	memset(&hori, 0, sizeof(t_intersect));
	memset(&vert, 0, sizeof(t_intersect));
	horizontal_intersect(game, game->player, &hori, *ray);
	vertical_intersect(game, game->player, &vert, *ray);
	calculate_distances(&hori, &vert, game);
	if (hori.dis < vert.dis)
	{
		ray->wall_hit_x = hori.hit_x;
		ray->wall_hit_y = hori.hit_y;
		ray->dist = hori.dis;
		ray->hit_hori = 1;
	}
	else
	{
		ray->wall_hit_x = vert.hit_x;
		ray->wall_hit_y = vert.hit_y;
		ray->dist = vert.dis;
		ray->hit_hori = 0;
	}
}
