#include "../../includes/cub3d.h"

static char	*skip_empty_lines(int fd, char *line)
{
    while (line && *line == '\n')
    {
        free(line);
        line = get_next_line(fd);
    }
    if (!line)
    {
        write(2, "Error: Empty map\n", 17);
        exit(1);
    }
    return (line);
}

static int	is_empty_line(char *line)
{
    int	j;

    j = 0;
    while (line[j] == ' ')
        j++;
    if (line[j] == '\n')
        return (1);
    return (0);
}

static char	**read_map_lines(int fd, char *line, t_game *game)
{
    char	**temp_map;
    char	*temp;
    int		i;
    int		len;

    i = 0;
    game->map.wight = 0;
    temp_map = malloc(sizeof(char *) * 2048);
    if (!temp_map)
        exit(1);
    while (line)
    {
        if (is_empty_line(line))
            break ;
        len = ft_strlen(line);
        if (line[len - 1] == '\n')
            len--;
        if (game->map.wight < len)
            game->map.wight = len;
        temp = ft_substr(line, 0, len);
        if (!is_chars_valid(temp))
        {
            write(2, "Error: Invalid character in map\n", 33);
            exit(1);
        }
        temp_map[i++] = temp;
        free(line);
        line = get_next_line(fd);
    }
    temp_map[i] = NULL;
    game->map.hight = i;
    return (temp_map);
}

static void	normalize_map_line(char *dest, char *src, int max_len)
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

static void	create_normalized_map(t_game *game, char **temp_map)
{
    int	i;

    game->map.map = malloc(sizeof(char *) * (game->map.hight + 1));
    if (!game->map.map)
        exit(1);
    i = 0;
    while (temp_map[i])
    {
        game->map.map[i] = malloc(game->map.wight + 1);
        if (!game->map.map[i])
            exit(1);
        normalize_map_line(game->map.map[i], temp_map[i], game->map.wight);
        free(temp_map[i]);
        i++;
    }
    game->map.map[i] = NULL;
    free(temp_map);
}

void	parse_map(t_game *game, int fd, char *line)
{
    char	**temp_map;

    line = skip_empty_lines(fd, line);
    temp_map = read_map_lines(fd, line, game);
    create_normalized_map(game, temp_map);
}