#include "../includes/minishell.h"

/* ECHO BUILTIN MODULE */

char	*trim_escape(char *str, char c, int mode, int *counts[3])
{
	char 	*str_copy;
	int	i;
	int	i2;
	
	i = 0;
	i2 = 0;
	if (!(str_copy = (char *)malloc(sizeof(char) * *counts[0])))
		exit(1);
	while (*(str + i))
	{
		if (*(str + i) != c || *(str + i - 1) == '\'')
			if (*(str + i) != '\n' || *(str + i - 1) != '\'')
				*(str_copy + i2++) = *(str + i);
		i++;
	}
	*(str_copy + i2) = '\0';
	*counts[0] = i2 + 1;
	return str_copy;
}

void	putnendl(char *str, char c, int mode, int *counts[3])
{
	while (*str == ' ' && str++)
		*counts[0] -= 1;
	str = trim_escape(str, c, mode, counts);
	//str = remove_gaps();
	write(1, str, *counts[0]);
	if (mode == 0)
		write(1, "\n", 1);
}

int	q_balanced(char *str, char c, int *counts[3])
{
	int	i;
	int	original;

	i  = 0;
	original = *counts[1];
	while (*(str + i))
	{
		if (*(str + i) == c)
			*counts[1] += 1;
		i++;
	}
	*counts[0] += i;
	if (c == 92)
		return ((*counts[1] == original) || (*counts[1] + 1) % 2);
	return ((*counts[1] + 1) % 2);
}

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

void	echo_1(char *str, int n, char c)
{
	char	*strs[2];
	int	*counts[3];

	assign_pointers(counts);
	if (q_balanced(str, c, counts))
		putnendl(str, c, n, counts);
	else
	{
		strs[0] = ft_strdup(str);
		while (write(1, ">", 1) && ((*counts[2] = get_next_line(0, &strs[1])) > 0))
		{
			strs[0] = ft_strjoin_free(strs[0], strs[1], '\n');
			if ((q_balanced(strs[1], c, counts)))
			{
				free(strs[1]);
				break;
			}
			free(strs[1]);
		}
		putnendl(strs[0], c, n, counts);
		free(strs[0]);
	}
	if (*counts[2] == -1)			
		read_error();
}

char	check_quotes(char *o_str)
{
	char *str[3] = { NULL };

	str[0] = ft_strchr(o_str, 39);
	str[1] = ft_strchr(o_str, 34);
	str[2] = ft_strchr(o_str, 92);
	while (str[0] && *str[0] && str[0] > o_str && *(str[0] - 1) == '\\')
		str[0] = ft_strchr(++str[0], '\'');
	while (str[1] && *str[1] && str[1] > o_str && *(str[1] - 1) == '\\')
		str[1] = ft_strchr(++str[1], '\"');
	while (str[2] && *str[2] && str[2] > o_str && *(str[2] - 1) == '\\')
		str[2] = ft_strchr(++str[2], '\\');
	if (str[0] && str[1])
		str[0] = (str[0] < str[1]) ? str[0] : str[1];
	else if (str[1]) 
		str[0] = str[1];
	else if (str[2] && !str[0] && !str[1] && *(str[2] + 1) == '\0')
		return (*str[2]);
	if (str[0])
		return (*str[0]);
	return (0);
}

int	echo_0(char *str)
{
	int 	*counts[3];
	char	c;

	assign_pointers(counts);
	while (*str == ' ')
		str++;
	str += 4;
	while (*str == ' ')
	{
		str++;
		if (*str == '-' && *(str + 1) == 'n' && (*(str + 2) == ' '|| *(str + 2) == '\0'))
		{
			*counts[2] = 1;
			str += 3;
		}
	}
	if ((c = check_quotes(str)))
		echo_1(str, *counts[2], c);
	else
		putnendl(str, 0, *counts[2], counts);
	return (1);
}
