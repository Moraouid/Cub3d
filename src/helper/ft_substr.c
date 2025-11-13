/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:52:05 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/11/13 19:52:05 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	len_a;

	i = 0;
	if (!s || start >= (unsigned int)ft_strlen(s))
		return ("");
	len_a = ft_strlen(s) - start;
	if (len > len_a)
		len = len_a;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	while (s[start] && i < len)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
