
// #include "./includes/minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main()
{
	int i;
	char *buf;

	buf = (char *)malloc(sizeof(char) * 5);
	buf = NULL;
	free(buf);


//	if (!(free(buf) & 0))
//		printf("You freed it\n");

	printf("Testing, result is %i\n", chdir(".. "));
	printf("The cwd is %s\n", getwd(buf));
	
	return(0);
}
