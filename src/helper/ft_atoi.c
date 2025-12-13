/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:46:51 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/13 22:54:59 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	skip_espace(char **str)
{
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
}

int	ft_atoi(char *str, int *error)
{
	long	num;

	num = 0;
	skip_espace(&str);
	if (*str < '0' || *str > '9')
		return (*error = 1, 0);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (*error = 1, 0);
	return ((int)(num));
}
