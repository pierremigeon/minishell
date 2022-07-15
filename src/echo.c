#include "../includes/minishell.h"

/* ECHO BUILTIN MODULE */

void	putnendl(char *str, char c, int mode)
{
	while (*str == ' ')
        	str++;
	while (*str)
	{
		if (*str != c)
			write(1, str, 1);
		str++;
	}
	if (mode == 0)
		write(1, "\n", 1);
}

char	get_ptr(char *str)
{
	char *ptr1;
	char *ptr2;

	ptr1 = ft_strchr(str, 92);
	ptr2 = ft_strchr(str, '"');
	if (ptr1 && ptr2) {
		printf("going to go with it\n");
		return ((ptr1 < ptr2) ? *ptr1 : *ptr2);
	}
	return ((ptr1) ? *ptr1 : *ptr2);
}

int	q_balanced(char *str, char c)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return ((count + 1) % 2);
}

void	echo_1(char *str, int n)
{
	char *str1, *str2;
	char c;
	int	i;

	i = 0;
	c = get_ptr(str);
	if (q_balanced(str, c))
		putnendl(str, c, n);
	else
	{
		str1 = ft_strdup(str);
		while (write(1, ">", 1) && ((i = get_next_line(0, &str2)) > 0))
		{
			str1 = ft_strjoin_free(str1, str2, '\n');
			free(str2);
			if (q_balanced(str1, c))
				break;
		}
		putnendl(str1, c, n);
		free(str1);
	}
	if (i == -1)			
		read_error();
}

int	echo_0(char *str)
{
	int 	n;

	n = 0;
	while (*str == ' ')
		str++;
	str += 4;
	while (*str == ' ')
	{
		str++;
		if (*str == '-' && *(str + 1) == 'n' && (*(str + 2) == ' '|| *(str + 2) == '\0'))
		{
			n = 1;
			str += 3;
		}
	}
	if ((ft_strchr(str, '\'')) || (ft_strchr(str, '"')))
		echo_1(str, n);
	else if (n)
		putnendl(str, 0, n);
	else
		putnendl(str, 0, n);
	return (1);
}
