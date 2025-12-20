/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:20:31 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/20 18:48:18 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_join(int fd, char *rem, t_game *game)
{
	char	*buffer;
	ssize_t	b_read;

	b_read = 1;
	if (BUFFER_SIZE < 0)
		return (NULL);
	while (b_read > 0 && !ft_strchr(rem, '\n'))
	{
		buffer = (char *)gc_malloc(&game->gc, sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0)
			return (NULL);
		if (b_read == 0)
			return (rem);
		buffer[b_read] = '\0';
		rem = ft_strjoin(rem, buffer, game);
	}
	return (rem);
}

static char	*line_extra(char **rem, t_game *game)
{
	char	*line;
	char	*new_line;
	char	*tmp;

	new_line = ft_strchr(*rem, '\n');
	if (!new_line)
		return (NULL);
	line = ft_substr_gnl(*rem, 0, new_line - *rem + 1, game);
	if (!line)
		return (NULL);
	tmp = ft_strdup_gnl(new_line + 1, game);
	if (!tmp)
		return (NULL);
	*rem = tmp;
	return (line);
}

char	*get_next_line(int fd, t_game *game)
{
	static char	*rem;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rem)
		rem = ft_strdup_gnl("", game);
	rem = read_join(fd, rem, game);
	if (!rem)
		return (NULL);
	line = line_extra(&rem, game);
	if (line)
		return (line);
	if (ft_strlen_gnl(rem) > 0)
	{
		line = ft_strdup_gnl(rem, game);
		rem = NULL;
		return (line);
	}
	return (rem = NULL, NULL);
}
