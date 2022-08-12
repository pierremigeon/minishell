#include "../includes/minishell.h"

/* ECHO BUILTIN MODULE */

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

int	iterate_ints(int *counts[3], int flag, char **str)
{
	*counts[0] = 1;

	if ((flag + 1) % 2)
		(*str)++;
	if (flag == 1 || flag == 2 || flag == 5)
		*counts[1] += 1;
	if (flag == 3 || flag == 4 || flag == 5)
		*counts[2] += 1;
	return (1);
}

int	t_newl(char *str, int locus)
{
	if (*str != '\n' || ((locus > 0 && *(str - 1) != '\\') || locus == 0))
		return(1);
	return (0);
}

int	bs_t(char *str, char c, int locus)
{
	if (*str == '\\' && locus > 0 && *(str - 1) == '\\')
		return (1);
	if (*str == c && locus > 0 && *(str - 1) == '\\')
		return (1);
	if (*str != c && *str != '\\')
		return (1);
	return (0);
}

char	*trim_escape(char *str, char c, int mode, int *counts[3])
{
	char 	*str_copy;
	int	*iterator[3];

	assign_pointers(iterator);
	if (!(str_copy = (char *)malloc(sizeof(char) * *counts[0])))
		exit(1);
	while (*str)
	{
		while (*str == '\\' && (*iterator[0] == 0 || *(str - 1) != '\\'))
			iterate_ints(iterator, 4, &str);
		if (*str == ' ' && (iterate_ints(iterator, 2, &str)))
			*(str_copy + *iterator[1] - 1) = *(str - 1);
		while ((*iterator[2] + 1 % 2) && *(str) == ' ')
			iterate_ints(iterator, 0, &str);
		if (bs_t(str, c, *iterator[0]))
			if (t_newl(str, *iterator[0]) && (*iterator[0] = 1))
				if (iterate_ints(iterator, 1, &str))
					*(str_copy + *iterator[1] - 1) = *str;
		(*str != '\0') ? ++str : 0;
	}
	*counts[0] = *iterator[1];
	return str_copy;
}

void	putnendl(char *str, char *c, int mode, int *counts[3])
{
	while (*str == ' ' && str++)
		*counts[0] -= 1;
	str = trim_escape(str, *c, mode, counts);
	write(1, str, *counts[0]);
	if (mode == 0)
		write(1, "\n", 1);
	free (str);
}

int	q_balanced(char *str, char *c, int *counts[3])
{
	int	i;
	int	orig;

	i  = 0;
	orig = *counts[1];
	while (*(str + i))
	{
		if (*(str + i) == *c)
			*counts[1] += 1;
		i++;
	}
	*counts[0] += i;
	if (*(c + 1) == 92)
		return (*counts[1] == orig || i > 0 && *(str + i - 1) != '\\');
	return ((*counts[1] + 1) % 2);
}

void	echo_1(char *str, int n, char *c)
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
				free (strs[1]);
				break;
			}
			free (strs[1]);
		}
		putnendl(strs[0], c, n, counts);
		free (strs[0]);
	}
	if (*counts[2] == -1)			
		read_error();
}

int	r_cbs(char *o_str, char *str)
{
	int 	i;

	i = 1;
	while ((str - i + 1) != o_str && *(str - i) == '\\')
		++i;
	return (i > 1 && (i + 1) % 2);
}

char	*check_quotes(char *o_str)
{
	char	*str[3] = { NULL };
	char	*out;

	out = ft_strnew(2);
	str[0] = ft_strchr(o_str, 39);
	str[1] = ft_strchr(o_str, 34);
	str[2] = ft_strrchr(o_str, '\\');
	if (str[2] && *str[2])
		if(*(str[2] + 1) != '\0' || r_cbs(o_str, str[2]))
			str[2] = NULL;
	while (str[0] && *str[0] && str[0] > o_str && *(str[0] - 1) == '\\')
		str[0] = ft_strchr(++str[0], '\'');
	while (str[1] && *str[1] && str[1] > o_str && *(str[1] - 1) == '\\')
		str[1] = ft_strchr(++str[1], '\"');
	if (str[0] && str[1])
		str[0] = (str[0] < str[1]) ? str[0] : str[1];
	else if (str[1])
		str[0] = str[1];
	if (str[0])
		out[0] = *str[0];
	if (str[2])
		out[1] = *str[2];
	return (out);
}

int	echo_0(char *str)
{
	int 	*counts[3];
	char	*c;

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
	if ((c = check_quotes(str)) && (*c || *(c + 1)))
		echo_1(str, *counts[2], c);
	else
	{
		*counts[0] = ft_strlen(str) + 1;
		putnendl(str, 0, *counts[2], counts);
	}
	free (c);
	return (1);
}
