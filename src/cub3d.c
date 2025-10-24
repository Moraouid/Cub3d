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


// void	parse_map(int fd, t_map *map)
// {
// 	char	*line;
//
// 	int i = 0;
// 	width_map(fd);
// 	map = malloc(sizeof(char *) * (game->map_width + 1));
// 	if (!map)
// 		(write(2, "Error: Memory allocation failed.\n", 33), exit(1));
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		map[i] = ft_strdup(line);
// 		if (map[i][ft_strlen(line) - 1] == '\n')
// 			game->map[i][ft_strlen(line) - 1] = '\0';
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	free(line);
// 	game->map[i] = NULL;
// 	close(fd);
// }

int	main(int ac, char **av)
{
    t_game game;
	int	i;
	int	fd;

	if (ac != 2)
	{
		write(2, "Error: Usage ./cub3d path_map.cub\n", 35);
		exit(1);
	}
	i = 0;
	while (av[1][i])
		i++;
	if (av[1][i - 1] != 'b' || av[1][i - 2] != 'u' || av[1][i - 3] != 'c'
		|| av[1][i - 4] != '.')
		return (write(2, "Error: Invalid map file\n", 24));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		write(2, "Error: map mot found\n", 21);
}
