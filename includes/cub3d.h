/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 23:28:33 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/13 22:47:29 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "./get_next_line/get_next_line.h"
#include "/usr/include/minilibx-linux/mlx.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WINDOW_W 1500
#define WINDOW_H 800
#define FOV (60 * M_PI / 180)
#define T_SIZE 32
#define MMSF 0.2
#define SPEED 0.7
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_ESC 65307
#define KEY_RIGHT 65361
#define KEY_LEFT 65363
#define WHITE 0XFFFFFF
#define RED 0x00FF0000
#define BLACK 0X000000
#define GRAY 0X808080

typedef struct s_gc
{
	void *ptr;
	struct s_gc *next;
} t_gc;

typedef struct s_teximg
{
	void *img;
	char *addr;
	int width;
	int height;
	int bits_per_pixel;
	int line_len;
	int endian;
	bool flag;
} t_teximg;

typedef struct s_texture
{
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
} t_texture;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_keymove
{
	int w;
	int a;
	int s;
	int d;
	int right;
	int left;
} t_keymove;

typedef struct s_player
{
	float x;
	float y;
	int flag;
	float angle;
} t_player;

typedef struct t_map
{
	char **map;
	int height;
	int width;
} t_map;

typedef struct s_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img;

typedef struct s_mlx
{
	void *mlx;
	void *win;
} t_mlx;

typedef struct s_intersect
{
	bool hit;
	float dis;
	float next_x;
	float next_y;
	float first_x;
	float first_y;
	float delta_x;
	float delta_y;
	float hit_x;
	float hit_y;
} t_intersect;

typedef struct s_ray
{
	bool facing_up;
	bool facing_left;
	bool facing_down;
	bool facing_right;
	float dist;
	bool hit_hori;
	float ray_angle;
	float angle_step;
	float wall_hit_x;
	float wall_hit_y;
} t_ray;

typedef struct s_render
{
	float h_offset;
	float wall_h;
	float start;
	float end;
} t_render;

typedef struct s_game
{
	t_gc *gc;
	t_map map;
	t_mlx mlx;
	t_img img;
	t_texture tex;
	t_teximg north;
	t_teximg south;
	t_teximg east;
	t_teximg wast;
	t_color floor;
	t_color ceiling;
	t_player player;
	t_keymove keymove;
} t_game;

void *gc_malloc(t_gc **gc, size_t size);
char **ft_split(char *s, char c, t_game *game);
char *ft_substr(char *s, unsigned int start, size_t len, t_gc **gc);
char *ft_strdup(char *s, t_gc **gc);

float normalize_angle(float angle);
void init_img(t_game *game);
void start_game(t_game *game);
void my_mlx_pixel_put(t_img *data, int x, int y, int color);
void render_mini_map(t_game *game);
void draw_square(t_game *game, float x, float y, int color);
void draw_circle(t_game *game, float x, float y, float radius);
int cant_move(t_game *game, char key);
int move_player(t_game *game);
int key_press(int key, t_game *game);
int release_key_press(int key, t_game *game);
int is_wall(t_game *game, float x, float y);
void ceiling_and_floor(t_game *game, int ceiling, int floor);
int ft_strlen(char *s);
void draw_ray(t_game *game, float angle, int length);
void raycasting(t_game *game);
void set_player_orientation(t_game *game, int x, int y, char c);
void get_facing(t_ray *ray, float angle);
void dist_calcule(t_game *game, t_ray *ray);
void vertical_intersect(t_game *game, t_player p, t_intersect *vert,
						t_ray ray);
void horizontal_intersect(t_game *game, t_player p,
						  t_intersect *hori, t_ray ray);
void hit_wall(t_game *game, t_intersect *inter);
void load_texture(t_game *game, t_teximg *tex, char *path);
char *init_var(t_game *game, char *line, int fd);
void init_game(t_game *game);
void parse_map(t_game *game, int fd, char *line);
int check_dot(char *line);
int hight_map(int fd);
void gc_clean(t_gc **gc);
void parse_color(char *line, t_color *color, t_game *game);
int is_chars_valid(char *line);
int cheking_map_walls(t_map map);
int the_zero_rule(t_map map);
void render3d(t_game *game, t_ray ray, int x);
int get_tex_pixel(t_teximg *tex, int x, int y);
int my_exit(t_game *game);
int ft_atoi(char *str, int *error);

#endif
