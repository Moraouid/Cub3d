/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 23:28:33 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/11/27 06:52:20 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./get_next_line/get_next_line.h"
# include "/usr/include/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WINDOW_W 1080
# define WINDOW_H 720
# define T_SIZE 16
# define SPEED 0.3
# define FOV 60 * M_PI / 180
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_RIGHT 65361
# define KEY_LEFT 65363
# define WHITE 0XFFFFFF
# define RED 0x00FF0000
# define BLACK 0X000000
# define GRAY 0X808080

typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;

typedef struct s_texture
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
}				t_texture;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_player
{
	int			facing_up;
	int			facing_left;
	int			facing_down;
	int			facing_right;
	bool		flag;
	float		x;
	float		y;
	float		angle;
}				t_player;

typedef struct s_dda
{
	int			x_map;
	int			y_map;
	int			x_step;
	int			y_step;
	int			side;
	float		s_distx;
	float		s_disty;
	float		d_distx;
	float		d_disty;
}				t_dda;

typedef struct s_keymove
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			right;
	int			left;
}				t_keymove;

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
}				t_map;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

typedef struct s_intersect
{
	float		dis;
	float		hit_x;
	float		hit_y;
	float		next_x;
	float		next_y;
	float		first_x;
	float		first_y;
	float		delta_x;
	float		delta_y;
}				t_intersect;

typedef struct s_game
{
	t_gc		*gc;
	t_map		map;
	t_img		img;
	t_mlx		mlx;
	t_color		ceiling;
	t_color		floor;
	t_player	player;
	t_texture	tex;
	t_keymove	keymove;
	t_intersect	vert;
	t_intersect	hori;

}				t_game;

int				ft_strlen(char *s);
char			*ft_strdup(char *s, t_gc **gc);
char			**ft_split(char *s, char c, t_gc **gc);
char			*ft_substr(char *s, unsigned int start, size_t len);
void			start_game(t_game *game);
void			*gc_malloc(t_gc **gc, size_t size);

#endif
