#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

void	int_changer(int *a[]) {
	*a[0] += 500;
	*a[1] += 5000;
	*a[2] += 50000;
}


void	assign_pointers(int	*test[3]) 
{
	int i = 0;

	while (i < 3) 
	{	
		if(!(test[i] = (int *)malloc(sizeof(int) * 1)))
			exit(1);	
		*test[i] = 5;
		++i;
	}
}

int	main() {

	int	*test[3];

	assign_pointers(test);

	printf("The first value is %i, %i, %i\n", *test[0], *test[1], *test[2]);

	int_changer(test);

	printf("The new value is %i, %i, %i\n", *test[0], *test[1], *test[2]);

	return (0);
}
