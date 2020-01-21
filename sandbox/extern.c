#include <stdio.h>


int	main()
{
	extern char	**environ;

	printf ("%s\n", *environ);	


	return (0);
}
