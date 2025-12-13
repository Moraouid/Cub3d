/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:46:51 by ozemrani          #+#    #+#             */
/*   Updated: 2025/12/13 23:05:26 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_atoi(char *nptr, int *error)
{
    int	i;
    int	sign;
    int	n;

    i = 0;
    sign = 1;
    n = 0;
    while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
        i++;
    if (nptr[i] == '-' || nptr[i] == '+')
    {
        if (nptr[i] == '-')
            sign *= -1;
        i++;
    }
    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        n = n * 10 + (nptr[i] - '0');
        i++;
    }
    while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
        i++;
    if (nptr[i] != '\0')
        *error = 1;
    else
        *error = 0;
    return (n * sign);
}
