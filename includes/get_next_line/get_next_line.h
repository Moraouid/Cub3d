/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:20:29 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/20 23:04:20 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../cub3d.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_game	t_game;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd, t_game *game);
char	*ft_strjoin(char *s1, char *s2, t_game *game);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen_gnl(const char *s);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len,
			t_game *game);
char	*ft_strdup_gnl(const char *src, t_game *game);

#endif
