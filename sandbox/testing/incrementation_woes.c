


#include <stdlib.h>
#include <stdio.h>


void    assign_pointers(int     *counts[3])
{       
        int i = 0;
        
        while (i < 3)
        {       
                if(!(counts[i] = (int *)malloc(sizeof(int) * 1)))
                        exit(1);
                *counts[i] = 0;
                ++i;
        }
}

int	main()
{
	int *array[50];

	assign_pointers(array);
	if (1 && (*array[0] += 5))
		*array[0] += 4;	
	printf("second pointer is %i\n", *array[0]);

	int i = 0;

	*array[++i] = 5;

	printf("is is %i\n", i);


	return (0);
}
