/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 23:14:00 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/22 21:12:27 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;
	int		fd;

	if (ac != 2)
	{
		write(2, "Error:\nUsage ./cub3d path_map.cub\n", 35);
		exit(1);
	}
	game = malloc(sizeof(t_game));
	ft_memset(game, 0, sizeof(t_game));
	ft_memset(&game->ceil, -1, sizeof(t_color));
	ft_memset(&game->floor, -1, sizeof(t_color));
	check_extension(av[1], ".cub");
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error:\nmap mot found\n", 21);
		my_exit(game);
	}
	parse_file(fd, game);
	validate_map(game);
	start_game(game);
	return (0);
}
