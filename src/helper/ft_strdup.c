/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:51:57 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/22 03:02:58 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_strdup(char *s, t_gc **gc)
{
	size_t	len;
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	dup = gc_malloc(gc, len);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	if(dup[i - 1] == '\n')
		i--;
	dup[i] = '\0';
	return (dup);
}
