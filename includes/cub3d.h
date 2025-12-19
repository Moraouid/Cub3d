/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 23:28:33 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/19 17:06:47 by sel-abbo         ###   ########.fr       */
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

// FOV = (60 * M_PI / 180)
# define WINDOW_W 1500
# define WINDOW_H 800
# define FOV 1.0471975512
# define T_SIZE 32
// # define MMSF 0.2
# define SPEED 0.7
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

typedef struct s_flags
{
	int			floor_set;
	int			ceiling_set;
}				t_flags;

typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;

typedef struct s_teximg
{
	int			width;
	int			height;
	int			endian;
	int			line_len;
	int			bits_per_pixel;
	void		*img;
	char		*addr;
}				t_teximg;

typedef struct s_texture
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
}				t_texture;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_keymove
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keymove;

typedef struct s_player
{
	int			corner_x;
	int			corner_y;
	float		x;
	float		y;
	float		angle;
}				t_player;

typedef struct t_map
{
	int			height;
	int			width;
	char		**map;
}				t_map;

typedef struct s_img
{
	int			endian;
	int			line_length;
	int			bits_per_pixel;
	void		*img;
	char		*addr;
}				t_img;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

typedef struct s_intersect
{
	bool		hit;
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

typedef struct s_ray
{
	bool		hit_hori;
	bool		facing_up;
	bool		facing_left;
	bool		facing_down;
	bool		facing_right;
	float		dist;
	float		ray_angle;
	float		angle_step;
	float		wall_hit_x;
	float		wall_hit_y;
}				t_ray;

typedef struct s_render
{
	bool		tex_flag;
	float		end;
	float		start;
	float		wall_h;
	float		h_offset;
}				t_render;

typedef struct s_game
{
	t_gc		*gc;
	t_map		map;
	t_mlx		mlx;
	t_img		img;
	t_color		floor;
	t_color		ceil;
	t_player	player;
	t_teximg	north;
	t_teximg	south;
	t_teximg	east;
	t_teximg	wast;
	t_texture	tex;
	t_keymove	keymove;
	float		sf;
}				t_game;

/*-----------------------------helper functions------------------------------*/
int				ft_strlen(char *s);
int				my_exit(t_game *game);
int				ft_atoi(char *str, int *error);
int				ft_strncmp(char *s1, char *s2, size_t n);
char			*ft_strrchr(char *s, int c);
char			*ft_strdup(char *s, t_gc **gc);
char			**ft_split(char *s, char c, t_game *game);
char			*ft_substr(char *s, unsigned int start, size_t len, t_gc **gc);
void			gc_clean(t_gc **gc);
void			*gc_malloc(t_gc **gc, size_t size);
void			*ft_memset(void *s, int c, size_t n);

/*--------------------------------parsing------------------------------------*/
int				hight_map(int fd);
int				the_zero_rule(t_map map);
int				is_empty_line(char *line);
int				is_chars_valid(char *line);
int				check_extension(char *filename, char *ext);
char			*init_var(t_game *game, char *line, int fd);
char			*skip_empty_lines(int fd, char *line, t_game *game);
char			*process_map_line(char *line, int *len, t_game *game);
char			**resize_map_array(char **temp_map, int *capacity,
					int old_capacity, t_game *game);
void			init_game(t_game *game);
void			validate_map(t_game *game);
void			parse_file(int fd, t_game *game);
void			parse_color(char *line, t_color *color, t_game *game);
void			normalize_map_line(char *dest, char *src, int max_len);

/*-----------------------------------mlx-------------------------------------*/
int				release_key_press(int key, t_game *game);
int				get_tex_pixel(t_teximg *tex, int x, int y);
void			init_img(t_game *game);
void			load_texture(t_game *game, t_teximg *tex, char *path);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);

/*---------------------------------rendring----------------------------------*/
int				move_player(t_game *game);
int				key_press(int key, t_game *game);
int				is_wall(t_game *game, float x, float y);
int				check_wall(t_game *game, float x, float y);
void			start_game(t_game *game);
void			raycasting(t_game *game);
void			render_mini_map(t_game *game);
void			get_facing(t_ray *ray, float angle);
void			dist_calcule(t_game *game, t_ray *ray);
void			render3d(t_game *game, t_ray ray, int x);
void			hit_wall(t_game *game, t_intersect *inter);
void			draw_ray(t_game *game, float angle, int length);
void			corner_of_player(t_game *game, float angle, int flag);
void			draw_square(t_game *game, float x, float y, int color);
void			ceiling_and_floor(t_game *game, int ceiling, int floor);
void			draw_circle(t_game *game, float x, float y, float radius);
void			set_player_orientation(t_game *game, int x, int y, char c);
void			vertical_intersect(t_game *game, t_player p, t_intersect *vert,
					t_ray ray);
void			horizontal_intersect(t_game *game, t_player p,
					t_intersect *hori, t_ray ray);
float			normalize_angle(float angle);

#endif
