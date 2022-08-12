
#include <stdio.h>
#include <stdlib.h>

void	change_pointer(char **str) {

	char *newstring;
	int i;

	i = 0;
	if (!(newstring = (char *)malloc(sizeof(char *) * 10)))
		exit(0);
	while (i < 9)
		*(newstring + i++) = 'P';
	*(newstring + i) = '\0';
	*(str + 1) = newstring;
}


char	**init_str(){
	char **str;
	int i;
	int x;

	i = 0;
	if (!(str = (char **)malloc(sizeof(char *) * 10)))
		exit(0);
	while (i < 10)
		if (!(*(str + i++) = (char *)malloc(sizeof(char) * 10)))
			exit(0);
	i = 0;
	while (i < 10)
	{
		x = 0;
		while (x < 10)
			*(*(str + i) + x++) = 'X';
		*(*(str + i++) + x) = '\0';
	}
	return str;
}

int	main()
{
	char **str;

	str = init_str();

	printf("The string initially is %s\n", *str);
	change_pointer(str);
	printf("The first string now is %s\n", *str);
	printf("The second string now is %s\n", *(str + 1));


	return (0);
}
