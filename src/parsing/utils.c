/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:12:13 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/22 05:14:36 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_extension(char *filename, char *ext)
{
	char	*dot;
	int		len;
	int		ext_len;

	len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (len < ext_len)
		return (0);
	dot = strrchr(filename, '.');//!
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
