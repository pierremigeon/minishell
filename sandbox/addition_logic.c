

#include <stdio.h>






int	test(void)
{
	return (0);
}

int	main()
{
	int n = 1;

	if ((n += test()))
		printf ("Hooray!\n");

	return (0);
}
