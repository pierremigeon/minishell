
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
	*str = newstring;
}


char	*init_str(){
	char *str;
	int i;

	i = 0;
	if (!(str =(char *)malloc(sizeof(char *) * 10)))
		exit(0);
	while (i < 9)
		*(str + i++) = 'X';
	*(str + i) = '\0';
	return str;
}

int	main()
{
	char *str;

	str = init_str();

	printf("The string initially is %s\n", str);
	change_pointer(&str);
	printf("The string now is %s\n", str);


	return (0);
}
