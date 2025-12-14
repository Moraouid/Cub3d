/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:12:10 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/14 06:30:43 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**read_map_lines(int fd, char *line, t_game *game)
{
	char	**temp_map;
	int		i;
	int		len;
	int		capacity;

	i = 0;
	capacity = 10;
	game->map.width = 0;
	temp_map = gc_malloc(&game->gc, sizeof(char *) * capacity);
	while (line)
	{
		if (is_empty_line(line))
			break ;
		if (i >= capacity - 1)
			temp_map = resize_map_array(temp_map, &capacity, i, game);
		temp_map[i++] = process_map_line(line, &len, game);
		if (game->map.width < len)
			game->map.width = len;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	temp_map[i] = NULL;
	game->map.height = i;
	return (temp_map);
}

void	normalize_map_line(char *dest, char *src, int max_len)
{
	int	j;
	int	len;

	len = ft_strlen(src);
	j = 0;
	while (j < len)
	{
		dest[j] = src[j];
		j++;
	}
	while (j < max_len)
	{
		dest[j] = ' ';
		j++;
	}
	dest[max_len] = '\0';
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
		printf("Error: invalid path or less/more texture \n");
		my_exit(game);
	}
}
