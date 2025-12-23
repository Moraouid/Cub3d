/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 06:28:45 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/22 23:47:31 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*skip_empty_lines(int fd, char *line, t_game *game)
{
	while (line && *line == '\n')
	{
		line = get_next_line(fd, game);
	}
	if (!line)
		error_and_exit(game, "Invalid map");
	return (line);
}

int	is_empty_line(char *line)
{
	if (line[0] == '\n')
		return (1);
	return (0);
}

char	**resize_map_array(char **temp_map, int *capacity, int old_capacity,
		t_game *game)
{
	char	**new_map;
	int		i;

	*capacity *= 2;
	new_map = gc_malloc(&game->gc, sizeof(char *) * (*capacity));
	i = 0;
	while (i < old_capacity)
	{
		new_map[i] = temp_map[i];
		i++;
	}
	return (new_map);
}

char	*process_map_line(char *line, int *len, t_game *game, int *flag)
{
	char	*temp;

	*len = ft_strlen(line);
	if (line[*len - 1] == '\n')
		(*len)--;
	temp = ft_substr(line, 0, *len, &game->gc);
	if (!is_chars_valid(temp, flag))
		error_and_exit(game, "Invalid map");
	return (temp);
}
