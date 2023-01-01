#include "../includes/minishell.h"

/* CD BUILTIN MODULE */

int	rev_not_code(char *start, char *str)
{
	int	i;

	i = 1;
	while (*(str - i) == '\\' && (str - i) != start && i < 3)
		++i;
	if (i == 3 && ((str - i - 1) == start || *(str - i - 1) != '\\'))
		return (0);
	return (1);
}

int	not_code(char *str, int *count)
{
	int	i;

	i = 0;
	while (*(str + i) == '\\' && i < 3)
		++i;
	if (*(str + i) != '\\' && i == 3)
	{
		*count += 3;
		return (0);
	}
	return (1);
}

char	*edit_bs(char *str)
{
	char 	*start;
	char	*new;
	int	count;

	new = str;
	while (*new == ' ')
		new++;
	while ((new = ft_strchr(new + 1, ' ')))
		if (rev_not_code(str, new) && *(new + 1))
			break;
	if (new)
		*new = '\0';
	new = ft_strnew(ft_strlen(str));
	start = new;
	count = 0;
	while (str && *str)
	{
		while (*str && not_code(str, &count))
			*(new++) = *(str++);
		if (!(not_code(str, &count)))
			str += 3;
		if (*str == '\n' && !(rev_not_code(start, str)))
			str += 1;
	}
	*(new - count) = '\0';
	return (start);
}

void	cd_error(char *str)
{
	ft_putstr("minishell: cd: ");
	ft_putstr(str);
	ft_putstr(": No such file or directory\n");
}

const char *get_tilde(t_hlist **env_h)
{
	int key;
	t_hlist *ptr;

	key = get_key("HOME");
	ptr = env_h[key];
	while (ptr->next != NULL)
	{
		if(!(ft_strcmp(ptr->var_name, "HOME")))
			return ((const char *)ptr->contents);
		ptr = ptr->next;
	}
	return ((const char *)ptr->contents);
}

int	bcheck(char *str, int i)
{
	int x;

	x = 0;
	if (i > 0 && *(str + i - 1) == '\\')
		i -= 1;
	else
		return (0);
	while (i > 0 && *(str + i--) == '\\')
		++x;
	return (x % 2);
}

int	bcheck2(char *str, int i)
{
	int x;

	x = 0;
	while (i-- > 0 && *(str-- - 1) == '\\')
		++x;
	return (x % 2);
}


int	check_balanced(char *str, char *c)
{
	int	count[3] = { 0, 0, 0 };

	while (str && *str)
	{
		if (!*c && (*str == '\"' || *str == '\'') && !(count[0] = 0))
			*c = *str;
		else if (*c && *str == *c)
			count[0] += 1;
		if ((count[0]) % 2)
			*c = '\0';
		if (*str == '\\' && *(str + 1) == '\0')
			if (!bcheck(str - count[2], count[2]))
				count[1] = 1;
		count[2] += 1;
		++str;
	}
	return(count[0] % 2 && !count[1] || !*c && !count[1]); 
}

char	*multiline(char *str, char *special)
{
	int	i;
	char	*ptr[2];

	i = 0;
	ptr[0] = ft_strdup(str);
	while (write(1, ">", 1) && ((i = get_next_line(0, &ptr[1])) > 0))
	{
		ptr[0] = ft_strjoin_free(ptr[0], ptr[1], '\n');
		if (check_balanced(ptr[1], special))
		{
			free(ptr[1]);
			break;
		}
		free(ptr[1]);
	}
	if (i == -1)
		read_error();
	return (ptr[0]);
}

int     count_bs(char *str)
{
	int x;

	x = 0;
	while (*(str + x) && *(str + x) == '\\')
		x++;
	return (x - (x / 2));
}

int	count_single_bs(char *str)
{
	int	x;
	int 	c;

	x = c = 0;
	while (*str)
	{
		if (x && *(str - 1) != '\\' && *(str + 1) != '\\')
			if (*str == '\\')
				c++;
		if (!x && *(str + 1) != '\\')
			if (*str == '\\')
				c++;
		x = 1;
		str++;
	}
	return (c);
}

char    *copy_coding(char *str)
{
	*str++ = '\\';
	*str++ = '\\';
	*str++ = '\\';
	return (str);
}

void	set_c(char *str, char *c, int i)
{
	if (c[1] && (c[1] == '\"' || c[1] == '\'')) 
		if (i > 0 && *(str + i - 1) == *c)
			if (!bcheck(str, i - 1))
			{
				*c = '\0';
				c[1] = '\0';
			}
	if (*(str + i) != '\"' && *(str + i) != '\'' && c[0])
		c[1] = *(str + i);
	if (*(str + i) == '\"' || *(str + i) == '\'')
		if (c[0] && !bcheck(str, i))
			c[1] = *(str + i);
	if (*(str + i) == '\"' || *(str + i) == '\'')
		if (!c[0] && !bcheck(str, i))
			c[0] = *(str + i);
}

char	*set_pointers(char **str, char **start, char **c, int *i)
{
	char    *new_str;

	*i = 0;
	new_str = ft_strnew(3 * count_single_bs(*str) + ft_strlen(*str) + 1);
	*start = new_str;
	ft_bzero(*c,3);
	return (new_str);
}

char	*str_rmc(char **str, char *c)
{
	char	*new_str;
	char	*start;
	int	i;
	int	bscount;

	new_str = set_pointers(str, &start, &c, &i);
	while (*(*str + i) && (!(bscount = 0)))
	{
		set_c(*str, c, i);
		if (!c[0] || c[0] && c[1] && c[0] == c[1])
		{
			if (*(*str + i) == '\\')
				bscount = count_bs(*str + i);
			if (bscount == 1)
				new_str = copy_coding(new_str);
			i += bscount;
			while(*(*str + i) && *(*str + i) == '\\')
				*(new_str++) = *(*str + i++);
			if (*(*str + i) && (*(*str + i) != *c || bcheck(*str, i)))
				*(new_str++) = *(*str + i);
		}
		else if (c[0] && c[1] && c[0] != c[1])
			if (*(*str + i) != '\\' || *(*str + i + 1) != '\"') // && *(*str + i + 1) != '\'')
				*(new_str++) = *(*str + i);
		++i;
	}
	if (*str == str[2]) 
		free(str);
	return (start);
}

char	**allocate_pointers(char *str)
{	
	char	**out;
	int	i;

	i = 0;
	if (!(out = (char **)malloc(sizeof(char *) * 3)))
		exit (1);
	while (i < 3)
	{
		out[i] = str;
		i++;
	}
	return (out);	
}

void	trim_start(char	**str)
{
	while (**str == ' ')
		*str += 1;
	*str += 2;
	while (**str == ' ')
		*str += 1;
}

char	*trim_begin(char *str)
{
	char	**out = NULL;
	char	*c;

	trim_start(&str);
	out = allocate_pointers(str);
	while(str && *str)
	{
		while (out[1] && out[2] && *str)
		{
			c = check_quotes(str);
			out[1] = ft_strchr(str, *c);
			out[2] = ft_strchr((*(out + 1) + 1), *c);
			while (out[2] && bcheck2(out[2], out[2] - out[0]))
				out[2] = ft_strchr((*(out + 2) + 1), *c);
			str = (out[2] && *out[2]) ? out[2] + 1: out[2];
		}
		if ((out[1] && out[2] == NULL || c[1]) && (out[2] = out[0]))
			out[0] = multiline(*out, c);
		out[0] = str_rmc(out, c);
	}
	str = out[0];
	free(out);
	return (str);
}

int	cd(char *str, t_hlist **env_h)
{
	char *tmp;

	printf("str is %s upon entry cd()\n", str);
	str = trim_begin(str);
	printf("after trim str is %s\n", str);
	tmp = edit_bs(str);
	printf("tmp is %s at end\n", tmp);
	if (!*str || !*tmp) {
		chdir(get_tilde(env_h));
		return(1);
	}
	if(chdir((const char *)tmp))
		cd_error(tmp);
	free(tmp);
	free(str);
	return (1);
}
