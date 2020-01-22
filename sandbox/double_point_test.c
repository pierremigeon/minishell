


#include <stdio.h>


void	jump(char **str)
{
	(*str) += 5;
	printf("%s\n", *str);
}

int	main()
{
	char test[] = "testing this string";
	char *ptr;

	ptr = test;

	jump(&ptr);
	return (0);
}
