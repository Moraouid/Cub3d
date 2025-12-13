/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:12:10 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/13 06:21:20 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*skip_empty_lines(int fd, char *line, t_game *game)
{
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		write(2, "Error: Empty map\n", 17);
		my_exit(game);
	}
	return (line);
}

int	is_empty_line(char *line)
{
	int	j;

	j = 0;
	while (line[j] == ' ')
		j++;
	if (line[j] == '\n')
		return (1);
	return (0);
}

char	**resize_map_array(char **temp_map, int *capacity, int old_capacity,
		t_game *game)
{
	char	**new_map;
	int		i;

	*capacity *= 2;
	new_map = gc_malloc(&game->gc, sizeof(char *) * (*capacity));
	i = 0;
	while (i < old_capacity)
	{
		new_map[i] = temp_map[i];
		i++;
	}
	return (new_map);
}

char	*process_map_line(char *line, int *len, t_game *game)
{
	char	*temp;

	*len = ft_strlen(line);
	if (line[*len - 1] == '\n')
		(*len)--;
	temp = ft_substr(line, 0, *len, &game->gc);
	if (!is_chars_valid(temp))
	{
		write(2, "Error: Invalid character in map\n", 33);
		my_exit(game);
	}
	return (temp);
}

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
