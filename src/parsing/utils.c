/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:12:13 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/19 10:40:02 by sel-abbo         ###   ########.fr       */
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

	len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (len < ext_len)
		return (0);
	dot = strrchr(filename, '.');
	if (!dot || strncmp(dot, ext, ext_len + 1) != 0)
		return (0);
	return (1);
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
