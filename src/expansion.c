/* Expansions Module */
#include "../includes/minishell.h"

int	run_case_2(t_hlist **env_h)
{
	t_hlist *temp;

	temp = env_h[get_key("~")];
	while (ft_strcmp(temp->var_name, "~"))
		temp = temp->next;
	return (temp->con_len - temp->var_len + 1);
}

int	run_case_1(t_hlist **env_h, char *str, int *len)
{
	int 		i[3] = { 0 };
	char		*ptr;
	t_hlist 	*temp;

	if (*str == '$')
	{
		len++;
		str++;
	}
	if (!(ptr = ft_strchr(str, '/')) && (i[0] = 1))
		if (!(ptr = ft_strchr(str, ' ')) && (i[0] = 2))
			ptr = ft_strchr(str, 0);
	*ptr = '\0';
	temp = env_h[get_key(str)];
	while (temp && (i[1] = ft_strcmp(temp->var_name, str)))
		temp = temp->next;
	i[2] = (temp && i[1] == 0) ? temp->con_len - temp->var_len : -ft_strlen(str);
	if (i[0] == 0)
		*ptr = '/';
	else if (i[0] == 1)
		*ptr = ' ';
	return (i[2]);
}

int	case_1(char *str)
{
	if (*str == '$')
		return (1);
	if (*str == '~' && (*(str + 1) == ' ' || *(str + 1) == '\0'))
		return (1);
	return (0);
}

int	length_of_out(char *str, t_hlist **env_h)
{
	int 	len[4] = { 0 };
	t_hlist *temp;
	char 	*ptr;

	while (*(str + len[0]++) == ' ')
		--len[1];
	while (*(str + len[0]))
	{
		if (case_1(str + len[0]))
			len[1] += run_case_1(env_h, str + len[0], &len[0]);
		else if (*(str + len[0]) == '~' && *(str + len[0] + 1) == '/')
			len[1] += run_case_2(env_h);
		++len[0];
	}
	return (len[0] + len[1]);
}

char *trim_end(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (str[len] == ' ')
		str[len--] = '\0';
	return (str);
}

int	is_signal(char *str, int i)
{
	if (*(str + i) == '~' && (*(str + i + 1) == ' ' || *(str + i + 1) == '\0' || *(str + i + 1) == '/' ))
		if (i > 0 && *(str + i - 1) == ' ' || i == 0)
			return (1);
	if (*(str + i) == '$' && (*(str + i +  1) != ' ' && *(str + i + 1) != '\0'))
		return (1);
	return (0);
}

char	*get_val_tilde(t_hlist **env_h)
{
	t_hlist         *temp;
	int i = 0;

	temp = env_h[get_key("~")];
	while (temp && (i = ft_strcmp(temp->var_name, "~")))
		temp = temp->next;
	if (temp && i == 0)
		return (temp->contents);
	return (NULL);
}

char	*get_val(t_hlist **env_h, char *str)
{
	char 		*ptr = NULL;
	t_hlist 	*temp;
	int		i[2] = { 0 };

	if (*str == '$')
	{
		str++;
		if (!(ptr = ft_strchr(str, ' ')) && (++i[0]))
			if (!(ptr = ft_strchr(str, '/')) && (++i[0]))
				ptr = ft_strchr(str, '\0');
		*ptr = '\0';
		temp = env_h[get_key(str)];
		while (temp && (i[1] = ft_strcmp(temp->var_name, str)))
			temp = temp->next;
		if (i[0] == 0)
			*ptr = ' ';
		else if (i[0] == 1)
			*ptr = '/';
		if (temp && i[1] == 0)
			return (temp->contents);
		return (NULL);
	}
	else 
		return (get_val_tilde(env_h));
}

char	*expand_command(char *str, t_hlist **env_h)
{
	char 	*out;
	char	*new_s = NULL;
	int	x[2] = { 0 };

	x[0] = length_of_out(trim_end(str), env_h);
	if(!(out = (char *)malloc(sizeof(char) * ++x[0])))
		exit(1);
	x[0] = 0;
	while (*(str + x[0]) == ' ')
		++x[0];
	while (*(str + x[0]))
	{
		if (is_signal(str, x[0]))
		{
			new_s = get_val(env_h, str + x[0]);
			while (new_s && *new_s)
				out[x[1]++] = *new_s++;
			while (*(str + x[0]) && *(str + x[0]) != ' ' && *(str + x[0]) != '/')
				++x[0];
		}
		out[x[1]++] = *(str + x[0]++);
	}
	out[x[1]] = '\0';
	free(str);
	return (out);
}
