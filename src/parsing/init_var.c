/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:11:59 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/22 03:25:46 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	**skip_spaces(char *line, t_game *game)
{
	char	**tex;

	tex = ft_split(line, ' ', game);
	return (tex);
}

static int	parse_texture(t_game *game, char **tex)
{
	if (check_extension(tex[1], ".xpm"))
	{
		write(2, "Error: Texture file must have .xpm extension\n", 46);
		my_exit(game);
	}
	if (!ft_strncmp(tex[0], "NO", 3) && !game->tex.no_path)
		game->tex.no_path = ft_strdup(tex[1], &game->gc);
	else if (!ft_strncmp(tex[0], "SO", 3) && !game->tex.so_path)
		game->tex.so_path = ft_strdup(tex[1], &game->gc);
	else if (!ft_strncmp(tex[0], "WE", 3) && !game->tex.we_path)
		game->tex.we_path = ft_strdup(tex[1], &game->gc);
	else if (!ft_strncmp(tex[0], "EA", 3) && !game->tex.ea_path)
		game->tex.ea_path = ft_strdup(tex[1], &game->gc);
	else
		return (0);
	return (1);
}

static int	parse_color_line(t_game *game, t_flags *flags, char **tex)
{
	if (!ft_strncmp(tex[0], "F", 2) && ++flags->floor_set == 1)
		parse_color(tex[1], &game->floor, game);
	else if (!ft_strncmp(tex[0], "C", 2) && ++flags->ceiling_set == 1)
		parse_color(tex[1], &game->ceil, game);
	else
		return (0);
	return (1);
}

char	*init_var(t_game *game, char *line, int fd)
{
	t_flags	flags;
	char	**tex;

	flags.floor_set = 0;
	flags.ceiling_set = 0;
	while (line)
	{
		if (*line == '\n')
		{
			line = get_next_line(fd, game);
			continue ;
		}
		tex = skip_spaces(line, game);
		if (!parse_texture(game, tex) && !parse_color_line(game, &flags, tex))
			return (line);
		line = get_next_line(fd, game);
	}
	return (line);
}
