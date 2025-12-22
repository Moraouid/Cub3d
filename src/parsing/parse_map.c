/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:12:10 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/22 21:14:41 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*process_and_read_next(int fd, char *line, t_game *game, int *flag)
{
	int		len;
	char	*new_line;

	game->map.map[game->map.height] = process_map_line(line, &len, game, flag);
	if (game->map.width < len)
		game->map.width = len;
	game->map.height++;
	new_line = get_next_line(fd, game);
	return (new_line);
}

char	**read_map_lines(int fd, char *line, t_game *game)
{
	char	**temp_map;
	int		capacity;
	int		flag;

	flag = 0;
	capacity = 10;
	game->map.width = 0;
	game->map.height = 0;
	temp_map = gc_malloc(&game->gc, sizeof(char *) * capacity);
	while (line && !is_empty_line(line))
	{
		if (game->map.height >= capacity - 1)
			temp_map = resize_map_array(temp_map, &capacity, game->map.height,
					game);
		game->map.map = temp_map;
		line = process_and_read_next(fd, line, game, &flag);
	}
	line = get_next_line(fd, game);
	if (line != NULL || flag != 1)
	{
		write(2, "Error:\nInvalid content after map\n", 34);
		my_exit(game);
	}
	temp_map[game->map.height] = NULL;
	return (temp_map);
}

void	create_normalized_map(t_game *game, char **temp_map)
{
	int	i;

	game->map.map = gc_malloc(&game->gc, sizeof(char *) * (game->map.height
				+ 1));
	i = 0;
	while (temp_map[i])
	{
		game->map.map[i] = gc_malloc(&game->gc, game->map.width + 1);
		normalize_map_line(game->map.map[i], temp_map[i], game->map.width);
		i++;
	}
	game->map.map[i] = NULL;
}

void	parse_map(t_game *game, int fd, char *line)
{
	int		i;
	char	**t_map;

	i = -1;
	line = skip_empty_lines(fd, line, game);
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
		{
			write(2, "ERROR\ninvalid map\n", 19);
			my_exit(game);
		}
	}
	t_map = read_map_lines(fd, line, game);
	i = -1;
	while (t_map[game->map.height - 1][++i])
	{
		if (t_map[game->map.height - 1][i] != '1' && t_map[game->map.height
			- 1][i] != ' ' && t_map[game->map.height - 1][i++] != '\n')
		{
			write(2, "ERROR\ninvalid map\n", 19);
			my_exit(game);
		}
	}
	create_normalized_map(game, t_map);
}

void	parse_file(int fd, t_game *game)
{
	char	*line;
	char	*map_line;

	line = get_next_line(fd, game);
	map_line = init_var(game, line, fd);
	if (game->tex.no_path && game->tex.so_path && game->tex.we_path
		&& game->tex.ea_path && game->ceil.r != -1 && game->floor.r != -1)
	{
		if (map_line)
			parse_map(game, fd, map_line);
		else
		{
			write(2, "Error:\nNo map found\n", 21);
			my_exit(game);
		}
	}
	else
	{
		write(2, "Error:\nError in file\n", 21);
		my_exit(game);
	}
}
