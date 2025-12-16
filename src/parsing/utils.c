/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:12:13 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/16 01:22:47 by ozemrani         ###   ########.fr       */
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

int	check_extension(char *filename, char *ext)
{
	char	*dot;
	int		len;
	int		ext_len;

	len = strlen(filename);
	ext_len = strlen(ext);
	if (len < ext_len)
		return (0);
	dot = strrchr(filename, '.');
	if (!dot || strncmp(dot, ext, ext_len + 1) != 0)
		return (0);
	return (1);
}

void	check_remaining_lines(int fd, char *line, t_game *game)
{
	if (line != NULL)
	{
		printf("Error: Invalid content after map\n");
		free(line);
		my_exit(game);
	}
}

void	normalize_map_line(char *dest, char *src, int max_len)
{
	int	j;
	int	len;

	len = ft_strlen(src);
	j = 0;
	while (j < len)
	{
		dest[j] = src[j];
		j++;
	}
	while (j < max_len)
	{
		dest[j] = ' ';
		j++;
	}
	dest[max_len] = '\0';
}
