/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 23:28:33 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/10/24 19:17:03 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "/usr/include/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
    char    **map;

	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;

	int		f_color;
	int		c_color;

	char	**grid;
	int		width;
	int		height;

	double	player_x;
	double	player_y;
	char	player_dir;

}			t_map;

typedef struct s_game
{
	t_map	*map;
}			t_game;

#endif
