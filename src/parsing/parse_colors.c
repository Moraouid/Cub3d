/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:12:07 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/22 23:47:08 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	extract_color(char *color)
{
	int	n_color;
	int	error;

	n_color = ft_atoi(color, &error);
	if (n_color >= 0 && n_color <= 255 && error == 0)
		return (n_color);
	else
		return (-1);
}

int	count_commas(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

void	parse_color(char *line, t_color *color, t_game *game)
{
	char	**rgb;

	if (!line || count_commas(line) != 2)
		error_and_exit(game, "color");
	rgb = ft_split(line, ',', game);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		error_and_exit(game, "color");
	color->r = extract_color(rgb[0]);
	color->g = extract_color(rgb[1]);
	color->b = extract_color(rgb[2]);
	if (color->r == -1 || color->g == -1 || color->b == -1)
		error_and_exit(game, "color");
}
