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
    int     i;
    int		fd;

    if (ac != 2)
    {
        write(2, "Error: Usage ./cub3d path_map.cub\n", 35);
        exit(1);
    }
    game = malloc(sizeof(t_game));
    init_game(game);
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
    if(cheking_map_walls(game->map) || the_zero_rule(game->map))
    {
        printf("Error map\n");
        return (1);
    }
    i = 0;
    while (game->map.map[i])
    {
        printf("Line %d (len=%zu): [%s]\n", i, ft_strlen(game->map.map[i]), game->map.map[i]);
        i++;
    }
    return (0);
}
