
#include "./includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

int	main()
{
	int i;
	char *buf;

	printf("Testing, result is %i\n", chdir(".. "));
	printf("The cwd is %s\n", getwd(buf));
	
	return(0);
}
