


#include <stdio.h>



int	main()
{
	char	*str1 = "ABC";
	char 	*str2 = "123";

	while (*str1)
		str1 = str2++;

	printf("str1 is now %s\n", str1);

	return (0);
}
