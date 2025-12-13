/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:12:13 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/13 00:23:09 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	hight_map(int fd)
{
	char	*line;
	int		height;

	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (height);
}

int	check_dot(char *line)
{
	char	*dot;

	dot = strrchr(line, '.');
	if (!strncmp(line, "NO ", 3) || !strncmp(line, "SO ", 3) || !strncmp(line,
			"WE ", 3) || !strncmp(line, "EA ", 3))
	{
		if (!dot || strncmp(dot, ".xpm", 4) != 0)
		{
			write(2, "Error: Invalid map extension\n", 29);
			return (1);
		}
	}
	return (0);
}
