#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h> 

int		main(int argc, char **argv)
{
	int fd;
	char *line;
	int i;
	int r;

	i = 1;
	line = NULL;
	if (argc >= 2)
	{
	       	while (i < argc)
        	{
			fd = open(argv[i], O_RDONLY);
			while ((r = get_next_line(fd, &line)) > 0)
			{
				printf("%s\n", line);
				ft_memdel((void **)&line);
			}
			close (fd);
			i++;
        	}
	}
	return (0);
}
