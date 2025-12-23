/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:12:13 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/22 23:42:40 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	error_and_exit(t_game *game, const char *msg)
{
	if (msg)
	{
		write(2, "Error\n", 6);
		write(2, msg, ft_strlen((char *)msg));
		write(2, "\n", 1);
	}
	else
	{
		write(2, "Error\n", 6);
	}
	my_exit(game);
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
	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strncmp(dot, ext, ext_len + 1) != 0)
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
