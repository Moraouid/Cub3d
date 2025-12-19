/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:11:59 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/19 11:51:46 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_texture(char *line, t_game *game)
{
	if (check_extension(line, ".xpm"))
	{
		write(2, "Error: Texture file must have .xpm extension\n", 46);
		my_exit(game);
	}
	if (!ft_strncmp(line, "NO ", 3) && !game->tex.no_path)
		game->tex.no_path = ft_substr(line, 3, ft_strlen(line) - 4, &game->gc);
	else if (!ft_strncmp(line, "SO ", 3) && !game->tex.so_path)
		game->tex.so_path = ft_substr(line, 3, ft_strlen(line) - 4, &game->gc);
	else if (!ft_strncmp(line, "WE ", 3) && !game->tex.we_path)
		game->tex.we_path = ft_substr(line, 3, ft_strlen(line) - 4, &game->gc);
	else if (!ft_strncmp(line, "EA ", 3) && !game->tex.ea_path)
		game->tex.ea_path = ft_substr(line, 3, ft_strlen(line) - 4, &game->gc);
	else
		return (0);
	return (1);
}

static int	parse_color_line(char *line, t_game *game, t_flags *flags)
{
	if (!ft_strncmp(line, "F ", 2) && ++flags->floor_set == 1)
		parse_color(line, &game->floor, game);
	else if (!ft_strncmp(line, "C ", 2) && ++flags->ceiling_set == 1)
		parse_color(line, &game->ceil, game);
	else
		return (0);
	return (1);
}

char	*init_var(t_game *game, char *line, int fd)
{
	t_flags	flags;

	flags.floor_set = 0;
	flags.ceiling_set = 0;
	while (line)
	{
		if (*line == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!parse_texture(line, game) && !parse_color_line(line, game, &flags))
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	init_game(t_game *game)
{
	game->gc = NULL;
	game->map.map = NULL;
	game->mlx.mlx = NULL;
	game->tex.no_path = NULL;
	game->tex.we_path = NULL;
	game->tex.so_path = NULL;
	game->tex.ea_path = NULL;
	game->map.width = 0;
	game->map.height = 0;
	ft_memset(&game->ceil, -1, sizeof(t_color));
	ft_memset(&game->floor, -1, sizeof(t_color));
	ft_memset(&game->player, 0, sizeof(t_player));
	ft_memset(&game->keymove, 0, sizeof(t_keymove));
}
