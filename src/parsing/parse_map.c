#include "../../includes/cub3d.h"

void	parse_map(t_game *game, int fd, char *line)
{
    char	*temp;
    char	**temp_map;
    int		i, len, j, max_len;

    i = 0;
    max_len = 0;
    temp_map = malloc(sizeof(char *) * 2048);
    if (!temp_map)
        exit(1);
    while(line && *line == '\n')
    {
        free(line);
        line = get_next_line(fd);
    }
    if (!line)
    {
        write(2, "Error: Empty map\n", 17);
        exit(1);
    }
    // First pass: store lines and find max length
    while(line)
    {
        j = 0;
        while(line[j] == ' ')
            j++;
        if (line[j] == '\n')
            break ;
        len = ft_strlen(line);
        if (line[len - 1] == '\n')
            len--;
        if(max_len < len)
            max_len = len;
        temp = ft_substr(line, 0, len);
        if(!is_chars_valid(temp))
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
    game->map.wight = max_len;
    game->map.map = malloc(sizeof(char *) * (i + 1));
    if (!game->map.map)
        exit(1);
    i = 0;
    while(temp_map[i])
    {
        len = ft_strlen(temp_map[i]);
        game->map.map[i] = malloc(max_len + 1);
        if (!game->map.map[i])
            exit(1);
        j = 0;
        while(j < len)
        {
            game->map.map[i][j] = temp_map[i][j];
            j++;
        }
        while(j < max_len)
        {
            game->map.map[i][j] = ' ';
            j++;
        }
        game->map.map[i][max_len] = '\0';
        free(temp_map[i]);
        i++;
    }
    game->map.map[i] = NULL;
    free(temp_map);
}