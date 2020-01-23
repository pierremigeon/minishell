


#include "../../includes/minishell.h"







int	main()
{
	char *line;
	char *out = NULL;

	while (get_next_line(0, &line))
	{
		if (!out)
			out = ft_strdup(line);
		else
			out = ft_strjoin_free(out, line);
		printf ("%s\n", out);
		free(line);
	}
	return (0);
}
