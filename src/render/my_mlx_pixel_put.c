/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:21:14 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/19 20:50:51 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(int *)dst = color;
}

void	init_img(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx.mlx, WINDOW_W, WINDOW_H);
	if (!game->img.img)
		my_exit(game);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		my_exit(game);
}

void	load_texture(t_game *game, t_teximg *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx.mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
		my_exit(game);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		my_exit(game);
}
