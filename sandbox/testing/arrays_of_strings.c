
#include <stdlib.h> 
#include <stdio.h>
#include "../../libft/get_next_line.c"

char	**make_array(char *str)
{
	char 	**out;
	int	i;

	i = 0;
	if (!(out = (char **)malloc(sizeof(char *) * 3)))
		exit(1);
	while (i < 3)
		out[i++] = str;
	return (out);
}

int	main()
{
	char *str;
	char **out;
	char *line;
	int	i;

        while ((i = get_next_line(0, &line)) > 0)
        {
                if (*line)
		{
			out = make_array(line);			
			printf("out[0] is %s, out[1] is %s, out[2] is %s\n", out[0], out[1], out[2]);
			out[0] = out[1];
			out[2] = str;
			free(out);
		}
                printf("$> ");
                free(line);
        }
	return (0);
}
