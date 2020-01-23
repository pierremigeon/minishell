
#include <stdio.h>
#include <unistd.h>


void	jump(char **str)
{
	int	i;

	i = 0;
	//(*str) += 5;
	//printf("%s\n", *str);
	while (*((*str) + i))
		write(1, *str + i++, 1);

}

int	main()
{
	char test[] = "testing this string\n";
	char *ptr;

	ptr = test;

	jump(&ptr);
	return (0);
}
