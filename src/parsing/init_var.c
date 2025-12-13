/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:11:59 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/13 22:17:56 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*init_var(t_game *game, char *line, int fd)
{
    int		i;
    int		floor_set;
    int		ceiling_set;

    i = 0;
    floor_set = 0;
    ceiling_set = 0;
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
            game->tex.no_path = ft_substr(line, 3, ft_strlen(line) - 4, &game->gc);
        else if (!strncmp(line, "SO ", 3) && !game->tex.so_path)
            game->tex.so_path = ft_substr(line, 3, ft_strlen(line) - 4, &game->gc);
        else if (!strncmp(line, "WE ", 3) && !game->tex.we_path)
            game->tex.we_path = ft_substr(line, 3, ft_strlen(line) - 4, &game->gc);
        else if (!strncmp(line, "EA ", 3) && !game->tex.ea_path)
            game->tex.ea_path = ft_substr(line, 3, ft_strlen(line) - 4, &game->gc);
        else if (!strncmp(line, "F ", 2) && ++floor_set == 1)
            parse_color(line, &game->floor, game);
        else if (!strncmp(line, "C ", 2) && ++ceiling_set == 1)
            parse_color(line, &game->ceiling, game);
        else
            return (line);
        free(line);
        line = get_next_line(fd);
        i++;
    }
    return (line);
}

void	init_game(t_game *game)
{
	game->gc = NULL;
	game->map.map = NULL;
	game->map.height = 0;
	game->map.width = 0;
	game->tex.no_path = NULL;
	game->tex.so_path = NULL;
	game->tex.we_path = NULL;
	game->tex.ea_path = NULL;
	game->floor.r = -1;
	game->floor.g = -1;
	game->floor.b = -1;
	game->ceiling.r = -1;
	game->ceiling.g = -1;
	game->ceiling.b = -1;
	game->player.x = 0;
	game->player.y = 0;
	game->keymove.w = 0;
	game->keymove.a = 0;
	game->keymove.s = 0;
	game->keymove.d = 0;
	game->keymove.left = 0;
	game->keymove.right = 0;
}
