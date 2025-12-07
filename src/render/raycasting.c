/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:52:29 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/07 02:25:14 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	horizontal_intersect(t_game *game, t_player p, t_intersect *hori,
		t_ray ray)
{
	if (ray.facing_up)
		hori->first_y = floor(p.y / T_SIZE) * T_SIZE - 0.0001;
	else if (ray.facing_down)
		hori->first_y = floor(p.y / T_SIZE) * T_SIZE + T_SIZE;
	hori->first_x = (hori->first_y - p.y) / tan(ray.ray_angle) + p.x;
	if (ray.facing_up)
		hori->delta_y = -T_SIZE;
	else if (ray.facing_down)
		hori->delta_y = T_SIZE;
	hori->delta_x = hori->delta_y / tan(ray.ray_angle);
	hori->next_x = hori->first_x;
	hori->next_y = hori->first_y;
	hit_wall(game, hori);
}

void	vertical_intersect(t_game *game, t_player p, t_intersect *vert,
		t_ray ray)
{
	if (ray.facing_right)
		vert->first_x = floor(p.x / T_SIZE) * T_SIZE + T_SIZE;
	else if (ray.facing_left)
		vert->first_x = floor(p.x / T_SIZE) * T_SIZE - 0.0001;
	vert->first_y = p.y + (vert->first_x - p.x) * tan(ray.ray_angle);
	if (ray.facing_right)
		vert->delta_x = T_SIZE;
	else if (ray.facing_left)
		vert->delta_x = -T_SIZE;
	vert->delta_y = vert->delta_x * tan(ray.ray_angle);
	vert->next_x = vert->first_x;
	vert->next_y = vert->first_y;
	hit_wall(game, vert);
}

int get_tex_pixel(t_teximg *tex, int x, int y)
{
	char	*pixel_addr;

	if (x < 0 || y < 0)
		return (0);
	pixel_addr = tex->addr + (y * tex->line_len + x * (tex->bits_per_pixel
				/ 8));
	return (*(int *)pixel_addr);
}

// void	render3d(t_game *game, t_ray ray, int x)
// {
// 	t_teximg	*tex;
// 	int			tex_x;
// 	float		hit_offset;
// 	float		dis_project_plan;
// 	float		wall_height;
// 	float		start_draw;
// 	float		end_draw;

// 	dis_project_plan = (WINDOW_W / 2) / tan(FOV / 2);
// 	wall_height = (T_SIZE / ray.dist) * dis_project_plan;
// 	start_draw = (WINDOW_H / 2) - (wall_height / 2);
// 	if (start_draw < 0)
// 		start_draw = 0;
// 	end_draw = (WINDOW_H / 2) + (wall_height / 2);
// 	if (end_draw >= WINDOW_H)
// 		end_draw = WINDOW_H - 1;
// 	if (ray.hit_hori)
// 	{
// 		if (ray.facing_down)
// 			tex = &game->south;
// 		else
// 			tex = &game->north;
// 		hit_offset = fmod(ray.wall_hit_x, T_SIZE);
// 	}
// 	else
// 	{
// 		if (ray.facing_right)
// 			tex = &game->east;
// 		else
// 			tex = &game->wast;
// 		hit_offset = fmod(ray.wall_hit_y, T_SIZE);
// 	}
// 	tex_x = (int)((hit_offset / (float)T_SIZE) * (float)tex->width);
// 	while (start_draw <= end_draw)
// 	{
// 		my_mlx_pixel_put(&game->img, x, start_draw, 444);
// 		start_draw++;
// 	}
// }

void render3d(t_game *game, t_ray ray, int x)
{
    t_teximg    tex;
    float       hit_offset;
    int         tex_x;
    int         tex_y;
    float       step;
    float       tex_pos;
    float dis_project_plan = (WINDOW_W / 2) / tan(FOV / 2);
    float wall_height = (T_SIZE / ray.dist) * dis_project_plan;
    float start_draw = (WINDOW_H / 2) - (wall_height / 2);
    float end_draw = (WINDOW_H / 2) + (wall_height / 2);

    if (start_draw < 0)
        start_draw = 0;
    if (end_draw >= WINDOW_H)
        end_draw = WINDOW_H - 1;
    if (ray.hit_hori)
    {
        if (ray.facing_down)
            tex = game->south;
        else
            tex = game->north;
        hit_offset = fmod(ray.wall_hit_x, T_SIZE);
    }
    else
    {
        if (ray.facing_right)
            tex = game->east;
        else
            tex = game->wast;
        hit_offset = fmod(ray.wall_hit_y, T_SIZE);
    }
    tex_x = (int)((hit_offset / (float)T_SIZE) * tex.width);
    step = (float)tex.height / wall_height;
    tex_pos = (start_draw - (WINDOW_H / 2 - wall_height / 2)) * step;
    while (start_draw <= end_draw)
    {
        tex_y = (int)tex_pos;
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= tex.height)
            tex_y = tex.height - 1;
        int color = get_tex_pixel(&tex, tex_x, tex_y);
        my_mlx_pixel_put(&game->img, x, start_draw, color);
        tex_pos += step;
        start_draw++;
    }
}


void	raycasting(t_game *game)
{
	int		i;
	t_ray	ray;
	float	angle_offset;

	i = 0;
	memset(&ray, 0, sizeof(t_ray));
	ray.ray_angle = normalize_angle(game->player.angle - FOV / 2);
	ray.angle_step = FOV / WINDOW_W;
	while (i < WINDOW_W)
	{
		get_facing(&ray, ray.ray_angle);
		dist_calcule(game, &ray);
		angle_offset = ray.ray_angle - game->player.angle;
		ray.dist = ray.dist * cos(angle_offset);
		render3d(game, ray, i);
		ray.ray_angle = normalize_angle(ray.ray_angle + ray.angle_step);
		i++;
	}
}
