/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 23:14:00 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/23 01:43:30 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;
	int		fd;

	if (ac != 2)
		error_and_exit(NULL, "Usage ./cub3d path_map.cub");
	game = malloc(sizeof(t_game));
	ft_memset(game, 0, sizeof(t_game));
	ft_memset(&game->ceil, -1, sizeof(t_color));
	ft_memset(&game->floor, -1, sizeof(t_color));
	if (!check_extension(av[1], ".cub"))
		error_and_exit(game, "Map file must have .cub extension");
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_and_exit(game, "map not found");
	parse_file(fd, game);
	if (the_zero_rule(game->map))
		error_and_exit(game, "Invalid map");
	start_game(game);
	return (0);
}
