#include "../../includes/cub3d.h"

int	is_chars_valid(char *line)
{
    int	i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
            && line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int cheking_map_walls(t_map map)
{
    int i = 0;
    int j;
    int last_char_pos;

    while(map.map[i])
    {
        j = 0;
        while(map.map[i][j] == ' ')
            j++;
        if(map.map[i][j] != '1')
            return 1;
        last_char_pos = map.wight - 1;
        while(last_char_pos >= 0 && map.map[i][last_char_pos] == ' ')
            last_char_pos--;
        
        if(i == 0 || i == map.hight - 1)
        {
            while(j <= last_char_pos)
            {
                if(map.map[i][j] != '1' && map.map[i][j] != ' ')
                    return 2;
                j++;
            }
        }
        else
        {
            if(last_char_pos >= 0 && map.map[i][last_char_pos] != '1')
                return 3;
        }
        i++;
    }
    return 0;
}

int the_zero_rule(t_map map)
{
    int x = 0;
    int y;

    while(map.map[x])
    {
        y = 0;
        while(map.map[x][y])
        {
            if(map.map[x][y] == '0' && (map.map[x][y - 1] == ' ' 
                || map.map[x][y + 1] == ' ' || map.map[x - 1][y] == ' '
                || map.map[x + 1][y] == ' ' || map.map[x][y + 1] == '\0'))
                return 1;
            y++;
        }
        x++;
    }
    return 0;
}
