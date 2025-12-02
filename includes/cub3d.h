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
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

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

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_player
{
	int				x;
	int				y;
	char			dir;
}					t_palyer;

typedef struct t_map
{
	char			**map;
	int				hight;
	int				wight;
}					t_map;

typedef struct s_game
{
	t_gc			*gc;
	t_map			map;
	t_texture		tex;
	t_color			floor;
	t_color			ceil;
	t_palyer		player;
	
}					t_game;

void				*gc_malloc(t_gc **gc, size_t size);
char				**ft_split(char *s, char c, t_gc **gc);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(char *s, t_gc **gc);
void	parse_map(t_game *game, int fd, char *line);
int check_dot(char *line);
int	hight_map(int fd);
char	*init_var(t_game *game, char *line, int fd);
void    init_game(t_game *game);
void	parse_color(char *line, t_color *color, t_gc *gc);
int	extract_color(char *color);
void	parse_map(t_game *game, int fd, char *line);
int	is_chars_valid(char *line);
int cheking_map_walls(t_map map);
int the_zero_rule(t_map map);

#endif
