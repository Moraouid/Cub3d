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
    char	**temp_map;
    int		i, len, j, max_len;

    i = 0;
    max_len = 0;
    temp_map = malloc(sizeof(char *) * 2048);
    if (!temp_map)
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
    // First pass: store lines and find max length
    while(line)
    {
        j = 0;
        while(line[j] == ' ')
            j++;
        if (line[j] == '\n')
            break ;
        len = ft_strlen(line);
        if (line[len - 1] == '\n')
            len--;
        if(max_len < len)
            max_len = len;
        temp = ft_substr(line, 0, len);
        if(!is_chars_valid(temp))
        {
            write(2, "Error: Invalid character in map\n", 33);
            exit(1);
        }
        temp_map[i++] = temp;
        free(line);
        line = get_next_line(fd);
    }
    temp_map[i] = NULL;
    game->map.hight = i;
    game->map.wight = max_len;
    
    // Second pass: allocate fixed size and pad with spaces
    game->map.map = malloc(sizeof(char *) * (i + 1));
    if (!game->map.map)
        exit(1);
    i = 0;
    while(temp_map[i])
    {
        len = ft_strlen(temp_map[i]);
        game->map.map[i] = malloc(max_len + 1);
        if (!game->map.map[i])
            exit(1);
        j = 0;
        // Copy original content
        while(j < len)
        {
            game->map.map[i][j] = temp_map[i][j];
            j++;
        }
        // Fill remaining with spaces
        while(j < max_len)
        {
            game->map.map[i][j] = ' ';
            j++;
        }
        game->map.map[i][max_len] = '\0';
        free(temp_map[i]);
        i++;
    }
    game->map.map[i] = NULL;
    free(temp_map);
}

int check_dot(char *line)
{
    char *dot;

    dot = strrchr(line, '.');
    if(!strncmp(line, "NO ", 3) || !strncmp(line, "SO ", 3) 
        || !strncmp(line, "WE ", 3) || !strncmp(line, "EA ", 3))
    {
        if (!dot || strncmp(dot, ".txt", 4) != 0)
        {
            write(2, "Error: Invalid map extension\n", 29);
            return (1);
        }
    }
    return (0);
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
        if(check_dot(line))
            return line;
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

int cheking_map_walls(t_map map)
{
    int i = 0;
    int j;
    int last_char_pos;

    while(map.map[i])
    {
        j = 0;
        while(map.map[i][j] == ' ')
            j++;
        if(map.map[i][j] != '1')
            return 1;
        last_char_pos = map.wight - 1;
        while(last_char_pos >= 0 && map.map[i][last_char_pos] == ' ')
            last_char_pos--;
        
        if(i == 0 || i == map.hight - 1)
        {
            while(j <= last_char_pos)
            {
                if(map.map[i][j] != '1' && map.map[i][j] != ' ')
                    return 2;
                j++;
            }
        }
        else
        {
            if(last_char_pos >= 0 && map.map[i][last_char_pos] != '1')
                return 3;
        }
        i++;
    }
    return 0;
}

int the_zero_rule(t_map map)
{
    int x = 0;
    int y;

    while(map.map[x])
    {
        y = 0;
        while(map.map[x][y])
        {
            if(map.map[x][y] == '0' && (map.map[x][y - 1] == ' ' 
                || map.map[x][y + 1] == ' ' || map.map[x - 1][y] == ' '
                || map.map[x + 1][y] == ' ' || map.map[x][y + 1] == '\0'))
                return 1;
            y++;
        }
        x++;
    }
    return 0;
}

int	main(int ac, char **av)
{
	t_game	*game;
    int     i;
	int		fd;

	if (ac != 2)
	{
		write(2, "Error: Usage ./cub3d path_map.cub\n", 35);
		exit(1);
	}
	game = malloc(sizeof(t_game));
	// init_game(&game);
    int len = strlen(av[1]);
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
	printf("no: %s\n", game->tex.no_path);
	printf("so: %s\n", game->tex.so_path);
	printf("wo: %s\n", game->tex.we_path);
	printf("eo: %s\n", game->tex.ea_path);
	printf("f: %d,%d,%d\n", game->floor.r, game->floor.g, game->floor.b);
	printf("c: %d,%d,%d\n", game->ceil.r, game->ceil.g, game->ceil.b);
    i = 0;
    printf("Map width (max_len): %d\n", game->map.wight);
    printf("Map height: %d\n", game->map.hight);
    while (game->map.map[i])
    {
        printf("Line %d (len=%zu): [%s]\n", i, ft_strlen(game->map.map[i]), game->map.map[i]);
        i++;
    }
    if(cheking_map_walls(game->map))
        printf("Error map\n");
    if(the_zero_rule(game->map))
        printf("the zero rule detecte\n");
    return (0);
}
