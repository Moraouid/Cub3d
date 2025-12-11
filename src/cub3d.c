/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 23:23:45 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/07 22:56:51 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		// free(map_line);
		printf("Error: invalid path or less/more texture \n");
		my_exit(game);
	}
}

int	main(int ac, char **av)
{
    t_game	*game;
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
        my_exit(game);
    }
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: map mot found\n", 21);
		my_exit(game);
	}
	parse_file(fd, game);
    if(cheking_map_walls(game->map) || the_zero_rule(game->map))
    {
        printf("Error map\n");
        my_exit(game);
    }
	start_game(game);
    return (0);
}
