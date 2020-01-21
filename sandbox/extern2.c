

#include <stdio.h>

int 	main(int argc, char *argv[], char * envp[])
{
	if (argc > 5)
		return (0);
	if (!argv[0])
		return (0);
	for (int i = 0; envp[i] != NULL; i++)
		printf("\n%s", envp[i]);
	return (0);
}
