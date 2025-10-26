/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 23:23:45 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/10/23 23:23:45 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	hight_map(int fd)
{
	char	*line;
	int		hight;

	line = get_next_line(fd);
	while (line)
	{
		hight++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (hight);
}
void	parse_map(int fd, t_map *map)
{
	char	*line;
	int		i;
	int		hight;

	i = 0;
	hight = hight_map(fd);
	map->map = malloc(sizeof(char *) * hight + 1);
	if (!map)
		(write(2, "Error: Memory allocation failed.\n", 33), exit(1));
	line = get_next_line(fd);
	while (line != NULL)
	{
		map->map[i] = ft_strdup(line);
		if (map->map[i][ft_strlen(line) - 1] == '\n')
			map->map[i][ft_strlen(line) - 1] = '\0';
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	map->map[i] = NULL;
	close(fd);
}

void	init_game(t_game *game)
{
	game->map->map = NULL;
	game->map->grid = NULL;
	game->map->no_path = NULL;
	game->map->so_path = NULL;
	game->map->we_path = NULL;
	game->map->ea_path = NULL;
	game->map->width = 0;
	game->map->height = 0;
	game->map->c_color = 0;
	game->map->f_color = 0;
	game->map->player_x = 0;
	game->map->player_y = 0;
	game->map->player_dir = 0;
}

int	main(int ac, char **av)
{
	t_game	game;
	int		i;
	int		fd;

	memset(&game, 0, sizeof(t_game));
	if (ac != 2)
	{
		write(2, "Error: Usage ./cub3d path_map.cub\n", 35);
		exit(1);
	}
	i = 0;
    game.map = malloc(sizeof(t_map));
	// init_game(&game);
	while (av[1][i])
		i++;
	if (av[1][i - 1] != 'b' || av[1][i - 2] != 'u' || av[1][i - 3] != 'c'
		|| av[1][i - 4] != '.')
		return (write(2, "Error: Invalid map file\n", 24));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: map mot found\n", 21);
		exit(1);
	}
	parse_map(fd, game.map);
	i = 0;
	while (game.map->map[i])
	{
		printf("%s", game.map->map[i]);
		i++;
	}
}
