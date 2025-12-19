/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:12:16 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/18 21:23:38 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_chars_valid(char *line)
{
	static int	flag;
	int			i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			return (0);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
		{
			if (flag)
				return (0);
			flag = 1;
		}
		i++;
	}
	return (1);
}

int	the_zero_rule(t_map map)
{
	int	x;
	int	y;

	x = 0;
	while (map.map[x])
	{
		y = 0;
		while (map.map[x][y])
		{
			if (map.map[x][y] == '0' && (map.map[x][y - 1] == ' '
					|| map.map[x][y + 1] == ' ' || map.map[x - 1][y] == ' '
					|| map.map[x + 1][y] == ' ' || map.map[x][y + 1] == '\0'))
				return (1);
			y++;
		}
		x++;
	}
	return (0);
}

void	validate_map(t_game *game)
{
	if (the_zero_rule(game->map))
	{
		write(2, "Error: map\n", 12);
		my_exit(game);
	}
}
