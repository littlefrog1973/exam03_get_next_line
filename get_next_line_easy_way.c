//#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    int i = 0;
    int rd = 0;
    char character;

    if (BUFFER_SIZE <= 0)
        return (NULL);
    char *buffer = malloc(100000); // check before the current BUFFER_SIZE and then malloc
    while ((rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1)) > 0)
    {
        buffer[i++] = character;
        if (character == '\n')
            break;
    }
    buffer[i] = '\0';
    if (rd == -1 || i == 0 || (!buffer[i - 1] && !rd))
        return (free(buffer), NULL);
    return (buffer);
}
/*
#include <stdio.h>
#include <fcntl.h>
int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;


	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
//		(void) argv;
		while((line = get_next_line(fd)))
		{
			printf("%s", line);
			free(line);
		}
	}
	return (0);
}
*/
