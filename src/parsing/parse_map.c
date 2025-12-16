/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:12:10 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/16 01:24:29 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*process_and_read_next(int fd, char *line, t_game *game)
{
	int		len;
	char	*new_line;

	game->map.map[game->map.height] = process_map_line(line, &len, game);
	if (game->map.width < len)
		game->map.width = len;
	game->map.height++;
	free(line);
	new_line = get_next_line(fd);
	return (new_line);
}

char	**read_map_lines(int fd, char *line, t_game *game)
{
	char	**temp_map;
	int		capacity;

	capacity = 10;
	game->map.width = 0;
	game->map.height = 0;
	temp_map = gc_malloc(&game->gc, sizeof(char *) * capacity);
	while (line && !is_empty_line(line))
	{
		if (game->map.height >= capacity - 1)
			temp_map = resize_map_array(temp_map, &capacity,
					game->map.height, game);
		game->map.map = temp_map;
		line = process_and_read_next(fd, line, game);
	}
	free(line);
	line = get_next_line(fd);
	check_remaining_lines(fd, line, game);
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
	char	**temp_map;

	line = skip_empty_lines(fd, line, game);
	temp_map = read_map_lines(fd, line, game);
	create_normalized_map(game, temp_map);
}

void	parse_file(int fd, t_game *game)
{
	char	*line;
	char	*map_line;

	line = get_next_line(fd);
	map_line = init_var(game, line, fd);
	if (game->tex.no_path && game->tex.so_path && game->tex.we_path
		&& game->tex.ea_path)
	{
		if (map_line)
			parse_map(game, fd, map_line);
		else
		{
			printf("Error: No map found\n");
			my_exit(game);
		}
	}
	else
	{
		printf("Error: invalid path or less/more texture\n");
		my_exit(game);
	}
}
