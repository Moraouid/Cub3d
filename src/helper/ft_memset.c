/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:21:08 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/14 21:39:18 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			j;
	unsigned char	*st;

	j = 0;
	st = s;
	while (j < n)
	{
		st[j] = (unsigned char)c;
		j++;
	}
	return (s);
}
