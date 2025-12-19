/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 06:13:54 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/19 20:37:13 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	choose_texture(t_game *game, t_ray *ray, t_teximg *tex, t_render *rend)
{
	rend->tex_flag = 0;
	if (ray->hit_hori)
	{
		if (ray->facing_down)
		{
			*tex = game->south;
			rend->tex_flag = 1;
		}
		else
			*tex = game->north;
		rend->h_offset = fmod(ray->wall_hit_x, T_SIZE);
	}
	else
	{
		if (ray->facing_right)
			*tex = game->east;
		else
		{
			*tex = game->wast;
			rend->tex_flag = 1;
		}
		rend->h_offset = fmod(ray->wall_hit_y, T_SIZE);
	}
}

void	draw_wall(t_game *game, t_teximg tex, int x, t_render *rend)
{
	int		tex_x;
	int		tex_y;
	int		color;
	float	step;
	float	tex_pos;

	tex_x = (rend->h_offset / T_SIZE) * tex.width;
	if (rend->tex_flag)
		tex_x = tex.width - tex_x - 1;
	step = tex.height / rend->wall_h;
	tex_pos = (rend->start - (WINDOW_H / 2 - rend->wall_h / 2)) * step;
	while (rend->start <= rend->end)
	{
		tex_y = (int)tex_pos;
		color = get_tex_pixel(&tex, tex_x, tex_y);
		my_mlx_pixel_put(&game->img, x, (int)rend->start, color);
		tex_pos += step;
		rend->start++;
	}
}

void	render3d(t_game *game, t_ray ray, int x)
{
	t_teximg	tex;
	t_render	rend;

	if (ray.dist < 0.00004)
		ray.dist = 0.00004;
	rend.wall_h = (T_SIZE / ray.dist) * (WINDOW_W / 2) / tan(FOV / 2);
	rend.start = (WINDOW_H / 2) - (rend.wall_h / 2);
	rend.end = (WINDOW_H / 2) + (rend.wall_h / 2);
	if (rend.start < 0)
		rend.start = 0;
	if (rend.end >= WINDOW_H)
		rend.end = WINDOW_H - 1;
	choose_texture(game, &ray, &tex, &rend);
	draw_wall(game, tex, x, &rend);
}
