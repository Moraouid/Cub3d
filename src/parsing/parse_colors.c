/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:12:07 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/14 03:20:09 by sel-abbo         ###   ########.fr       */
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

void	parse_color(char *line, t_color *color, t_game *game)
{
	char	**rgb;
	int		i;

	i = 2;
	if (!line)
	{
		printf("Error_color1\n");
		my_exit(game);
	}
	rgb = ft_split(&line[i], ',', game);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		printf("Error_color2\n");
		my_exit(game);
	}
	color->r = extract_color(rgb[0]);
	color->g = extract_color(rgb[1]);
	color->b = extract_color(rgb[2]);
	if (color->r == -1 || color->g == -1 || color->b == -1)
	{
		printf("Error_color3\n");
		my_exit(game);
	}
}
