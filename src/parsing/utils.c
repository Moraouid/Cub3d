#include "../../includes/cub3d.h"

int	hight_map(int fd)
{
	char	*line;
	int		hight = 0;

	line = get_next_line(fd);
	while (line)
	{
		hight++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (hight);
}

int check_dot(char *line)
{
    char *dot;

    dot = strrchr(line, '.');
    if(!strncmp(line, "NO ", 3) || !strncmp(line, "SO ", 3) 
        || !strncmp(line, "WE ", 3) || !strncmp(line, "EA ", 3))
    {
        if (!dot || strncmp(dot, ".txt", 4) != 0)
        {
            write(2, "Error: Invalid map extension\n", 29);
            return (1);
        }
    }
    return (0);
}
