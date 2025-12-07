/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 23:23:45 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/07 01:07:10 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	height_and_width(t_game *game)
{
	int	h;
	int	w;
	int	i;

	h = 0;
	while (game->map.map[h])
		h++;
	game->map.height = h;
	i = 0;
	w = 0;
	while (i < h)
	{
		if (ft_strlen(game->map.map[i]) > w)
			w = ft_strlen(game->map.map[i]);
		i++;
	}
	game->map.width = w;
}

int	extract_color(char *color)
{
	int	n_color;

	n_color = atoi(color);
	if (n_color >= 0 && n_color <= 255)
		return (n_color);
	else
		return (-1);
}

void	parse_color(char *line, t_color *color, t_gc *gc)
{
	char	**rgb;
	int		i;

	i = 2;
	if (!line)
	{
		printf("Error_color1\n");
		exit(1);
	}
	rgb = ft_split(&line[i], ',', &gc);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		printf("Error_color2\n");
		exit(1);
	}
	color->r = extract_color(rgb[0]);
	color->g = extract_color(rgb[1]);
	color->b = extract_color(rgb[2]);
	if (color->r == -1 || color->g == -1 || color->b == -1)
	{
		printf("Error_color3\n");
		exit(1);
	}
}

int	is_chars_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	parse_map(t_game *game, int fd, char *line)
{
	char	*temp;

	int i, len, j;
	i = 0;
	game->map.map = malloc(sizeof(char *) * 2048);
	if (!game->map.map)
		exit(1);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		write(2, "Error: Empty map\n", 17);
		exit(1);
	}
	while (line)
	{
		j = 0;
		while (line[j] == ' ')
			j++;
		if (line[j] == '\n')
			break ;
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			len--;
		temp = ft_substr(line, 0, len);
		if (!is_chars_valid(temp))
		{
			write(2, "Error: Invalid character in map\n", 33);
			exit(1);
		}
		game->map.map[i++] = temp;
		free(line);
		line = get_next_line(fd);
	}
	game->map.map[i] = NULL;
	game->map.height = i;
}

int	check_dot(char *line)
{
	char	*dot;

	dot = strrchr(line, '.');
	if (!strncmp(line, "NO ", 3) || !strncmp(line, "SO ", 3) || !strncmp(line,
			"WE ", 3) || !strncmp(line, "EA ", 3))
	{
		if (!dot || strncmp(dot, ".xpm", 4) != 0)
		{
			write(2, "Error: Invalid map extension\n", 29);
			return (1);
		}
	}
	return (0);
}

char	*init_var(t_game *game, char *line, int fd)
{
	int	i;

	i = 0;
	while (line)
	{
		if (*line == '\n' && i < 6)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (check_dot(line))
			return (line);
		if (!strncmp(line, "NO ", 3) && !game->tex.no_path)
			game->tex.no_path = ft_substr(line, 3, ft_strlen(line) - 4);
		else if (!strncmp(line, "SO ", 3) && !game->tex.so_path)
			game->tex.so_path = ft_substr(line, 3, ft_strlen(line) - 4);
		else if (!strncmp(line, "WE ", 3) && !game->tex.we_path)
			game->tex.we_path = ft_substr(line, 3, ft_strlen(line) - 4);
		else if (!strncmp(line, "EA ", 3) && !game->tex.ea_path)
			game->tex.ea_path = ft_substr(line, 3, ft_strlen(line) - 4);
		else if (!strncmp(line, "F ", 2))
			parse_color(line, &game->floor, game->gc);
		else if (!strncmp(line, "C ", 2))
			parse_color(line, &game->ceiling, game->gc);
		else
			return (line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (line);
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
			exit(1);
		}
	}
	else
	{
		free(map_line);
		printf("Error: invalid path or less/more texture \n");
		exit(1);
	}
}

int	cheking_map_walls(t_map map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (map.map[i])
	{
		j = 0;
		len = ft_strlen(map.map[i]);
		while (map.map[i][j] == ' ')
			j++;
		if (map.map[i][j] != '1')
			return (1);
		if (i == 0 || i == map.height - 1)
		{
			while (j < len)
			{
				if (map.map[i][j] != '1' && map.map[i][j] != ' ')
					return (2);
				j++;
			}
		}
		else
		{
			if (map.map[i][len - 1] != '1')
				return (3);
		}
		i++;
	}
	return (0);
}

int	the_zero_rule(t_map map)
{
	int	x;
	int	y;

	x = 0;
	while (map.map[x])
	{
		y = 0;
		while (map.map[x][y])
		{
			if (map.map[x][y] == '0' && (map.map[x][y - 1] == ' '
					|| map.map[x][y + 1] == ' ' || map.map[x - 1][y] == ' '
					|| map.map[x + 1][y] == ' ' || map.map[x][y + 1] == '\0'))
				return (1);
			y++;
		}
		x++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;
	int		fd;
	int		len;

	if (ac != 2)
	{
		write(2, "Error: Usage ./cub3d path_map.cub\n", 35);
		exit(1);
	}
	game = malloc(sizeof(t_game));
	// init_game(&game);
	len = strlen(av[1]);
	if (len < 4 || strncmp(av[1] + len - 4, ".cub", 4) != 0)
	{
		write(2, "Error: Invalid map extension\n", 29);
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: map mot found\n", 21);
		exit(1);
	}
	parse_file(fd, game);
	height_and_width(game);
	memset(&game->player, 0, sizeof(t_player));
	memset(&game->keymove, 0, sizeof(t_keymove));
	if (cheking_map_walls(game->map))
		printf("Error map\n");
	if (the_zero_rule(game->map))
		printf("the zero rule detecte\n");
	start_game(game);
	return (0);
}
