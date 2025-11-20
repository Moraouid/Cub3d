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
	int		hight = 0;

	line = get_next_line(fd);
	while (line)
	{
		hight++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (hight);
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

	i = 1;
	while (line[i] == ' ')
		i++;
	if (!line)
	{
		printf("Error_color1\n");
		exit(1);
	}
	rgb = ft_split(line, ',', &gc);
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
    int		i, len;

    i = 0;
    game->map.map = malloc(sizeof(char *) * 2048);
    if (!game->map.map)
        exit(1);
    while(line && *line == '\n')
    {
        free(line);
        line = get_next_line(fd);
    }
    if (!line)
    {
        write(2, "Error: Empty map\n", 17);
        exit(1);
    }
    while(line)
    {
        if (line[0] == '\n')
            break ;
		len = ft_strlen(line);
        if (line[len - 1] == '\n')
            len--;
        temp = ft_substr(line, 0, len);
        if(!is_chars_valid(temp))
        {
            write(2, "Error: Invalid character in map\n", 33);
            exit(1);
        }
        game->map.map[i++] = temp;
        free(line);
        line = get_next_line(fd);
    }
    game->map.map[i] = NULL;
    game->map.hight = i;
}

char	*init_var(t_game *game, char *line, int fd)
{
    int i = 0;

    while(line)
    {
        if (*line == '\n' && i < 6)
        {
            free(line);
            line = get_next_line(fd);
            continue ;
        }
        if(!strncmp(line, "NO ", 3) && !game->tex.no_path)
            game->tex.no_path = ft_substr(line, 3, ft_strlen(line) - 4);
        else if(!strncmp(line, "SO ", 3) && !game->tex.so_path)
            game->tex.so_path = ft_substr(line, 3, ft_strlen(line) - 4);
        else if(!strncmp(line, "WE ", 3) && !game->tex.we_path)
            game->tex.we_path = ft_substr(line, 3, ft_strlen(line) - 4);
        else if(!strncmp(line, "EA ", 3) && !game->tex.ea_path)
            game->tex.ea_path = ft_substr(line, 3, ft_strlen(line) - 4);
        else if(!strncmp(line, "F ", 2))
            parse_color(line, &game->floor, game->gc);
        else if(!strncmp(line, "C ", 2))
            parse_color(line, &game->ceil, game->gc);
        else
            return line;
        free(line);
        line = get_next_line(fd);
        i++;
    }
    return line;
}

void	parse_file(int fd, t_game *game)
{
    char	*line;
    char	*map_line;

    line = get_next_line(fd);
    map_line = init_var(game, line, fd);
    if(game->tex.no_path && game->tex.so_path && game->tex.we_path 
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

int	main(int ac, char **av)
{
	t_game	*game;
	int		i;
	int		fd;

	if (ac != 2)
	{
		write(2, "Error: Usage ./cub3d path_map.cub\n", 35);
		exit(1);
	}
	i = 0;
	game = malloc(sizeof(t_game));
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
	parse_file(fd, game);
	printf("no: %s\n", game->tex.no_path);
	printf("so: %s\n", game->tex.so_path);
	printf("wo: %s\n", game->tex.we_path);
	printf("eo: %s\n", game->tex.ea_path);
	printf("f: %d,%d,%d\n", game->floor.r, game->floor.g, game->floor.b);
	printf("c: %d,%d,%d\n", game->ceil.r, game->ceil.g, game->ceil.b);
    i = 0;
    while (game->map.map[i])
    {
        printf("%s\n", game->map.map[i]);
        i++;
    }
}
