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
# include "/usr/include/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WINDOW_W 1080
# define WINDOW_H 720
# define T_SIZE 32
# define SPEED 1.5
# define FOV 60 * M_PI / 180
# define WHITE 0XFFFFFF
# define RED 0x00FF0000
# define BLACK 0X000000
# define GRAY 0X808080

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}					t_gc;

typedef struct s_texture
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
}					t_texture;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_player
{
	float				x;
	float			y;
	float			angle;
	int				falg;
}					t_palyer;

typedef struct s_map
{
	char			**map;
	int				hight;
	int				wight;
}					t_map;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
}					t_mlx;

typedef struct s_game
{
	t_gc			*gc;
	t_map			map;
	t_img			img;
	t_mlx			mlx;
	t_texture		tex;
	t_color			floor;
	t_color			ceil;
	t_palyer		player;
	
}					t_game;

void				*gc_malloc(t_gc **gc, size_t size);
char				**ft_split(char *s, char c, t_gc **gc);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(char *s, t_gc **gc);
void				start_game(t_game *game);


#endif
