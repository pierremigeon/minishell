#include <unistd.h>
#include <stdlib.h>

//     int
//     chdir(const char *path);




int	main()
{
	int i;
	char str[] = " ";

	system("pwd");
	i = chdir(str);
	system("pwd");
	return (0);
}
