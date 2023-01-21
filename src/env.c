#include "../includes/minishell.h"

/* ENV, SETENV AND UNSETENV BUILTINS MODULE */

int	env(t_hlist **env_h)
{
	t_hlist *temp;

	temp = env_h[HASH_SIZE];
	while (temp)
	{
		ft_putstr(temp->var_name);
		ft_putchar('=');
		ft_putendl(temp->contents);
		temp = temp->next_2;
	}
	return (1);
}

int	set_env_error(char **args)
{
	free_args(args);
	write(1, "setenv: Too many arguments.\n", 28);
	return (1);
}
void	reset_variable(t_hlist *node, char *contents)
{
	free(node->contents);
	node->contents = ft_strdup(contents);
}

int	args_len(char **args)
{
	int	ret;

	ret = 0;
	while (args[ret])
		++ret;
	return (ret);
}

void	set_list_end(t_hlist *new_end, t_hlist **env_h)
{
	t_hlist *end = env_h[HASH_SIZE + 1];

	end->next_2 = new_end;
	new_end->last = end;
	env_h[HASH_SIZE + 1] = new_end;
}

char	**surgery(char **args)
{
	int	len;
	char	**new_args;

	len = 3 + 1;
	if (!(new_args = (char **)malloc(sizeof(char *) * len)))
		exit(1);
	new_args[--len] = NULL;
	new_args[--len] = ft_strdup("");
	while (--len >= 0)
		new_args[len] = ft_strdup(args[len]);
	free_args(args);
	return (new_args);
}

void	new_point(t_hlist **env_h, int key, char *str1, char *str2)
{
	env_h[key] = new_hash_node_2(str1, str2);
	if (!env_h[50] && !env_h[51])
	{
		env_h[50] = env_h[key];
		env_h[51] = env_h[key];
	}
	else
		set_list_end(env_h[key], env_h);
}

int	check_legal_chars(char *str)
{
	while (*str)	
	{
		if (!ft_isalnum(*str) && *str != '.' && *str != '_')
			return(1);
		++str;
	}
	return (0);
}

int	illegal_char_error(char **args, int i)
{
	if (i)
		free_args(args);
	write(1, "setenv: Variable name must contain alphanumeric characters.\n", 60);
	return (1);
}

int	start_error(char **args, int i)
{
	if (i)
		free_args(args);
	write(1, "setenv: Variable name must begin with a letter.\n", 48);
	return (1);
}

int	usage_statement_error(char **args)
{
	free_args(args);
	write(1, "usage: setenv [variable_name] [value] | [-h]\n", 45);
	return (1);
}

int	quotation_error(int i)
{
	if (i == -1)
		write(1, "Unmatched \'\"\'.\n", 15);
	if (i == -2)
		write(1, "Unmatched \'\'\'.\n", 15);
	return (1);
}

char	*trim_qs(int count, char *str)
{
	char *out;
	int i;
	int x;

	i = -1;
	x = 0;
	if (count == 0)
		return str;
	else if (count == -4 && start_error(&str, 0))
		return (NULL);
	else if (count == -3 && illegal_char_error(&str, 0))
		return (NULL);
	else if (count < 0 && quotation_error(count))
		return (NULL);
	if (!(out = (char *)malloc(sizeof(char) * count)))
		exit(1);
	while (str[++i])
		if (str[i] != '\"' && str[i] != '\'')
			out[x++] = str[i];
	out[x] = '\0';
	free(str);
	return (out);
}

void	set_counts(char c, int *c1, int *c2)
{
	if (*c1 == 0 && (*c2 += 1)) 
		*c1 = (c == '\"') ? -1 : -2;
	else if (*c1 == -1 && c == '\"' && ((*c2 -= 1) || 1)) 
		*c1 = 0;
	else if (*c1 == -2 && c == '\'' && ((*c2 -= 1) || 1)) 
		*c1 = 0;
	else 
		*c2 += 1 * (*c2 < 2);
}

int	count_qs(char *str)
{
	int i;
	int c1;
	int c2;
	int total;

	i = -1;
	c1 = c2 = total = 0;
	while(str[++i])
		if ((str[i] == '\"' || str[i] == '\'') && (total += 1))
			set_counts(str[i], &c1, &c2);
	if (total == 0)
		return (0);
	if (c1 < 0)
		return (c1);
	else if ((str[0] == '\"' || str[0] == '\'') && c2 == 0)
		return (-4);
	else if (c2 == 0)
		return (i - total + 1);
	else if (c2 > 0)
		return (-3);
	return (0);
}

char	**clean_args(char *str, t_hlist **env_h)
{
	char	**args;
	int	ar_len;

	args = ft_strsplit(str, ' ');
	if (args[1] != NULL && !(ft_strcmp(args[1], "-h")))
		if (usage_statement_error(args))
			return (NULL);
	if ((ar_len = args_len(args)) > 1)
		if (!(args[1] = trim_qs(count_qs(args[1]), args[1])))
			if(free_args(args))
				return (NULL);
	if (ar_len > 1 && !ft_isalpha(*(*(args + 1))) && *(*(args + 1)) != '_')
		if (start_error(args, 1))
			return (NULL);
	if (ar_len >= 4 && set_env_error(args))
		return (NULL);
	if (ar_len == 1 && free_args(args) && env(env_h))
		return (NULL);
	if (ar_len > 1 && check_legal_chars(args[1]) && illegal_char_error(args, 1))
		return (NULL);
	if (ar_len == 2)
		args = surgery(args);
	return (args);
}

int	set_env(char *str, t_hlist **env_h)
{
	t_hlist *temp;
	char 	**args;
	int	key;

	if (!(args = clean_args(str, env_h)))
		return (1);
	key = get_key(args[1]);

	if (!env_h[key])
		new_point(env_h, key, args[1], args[2]);
	else
	{
		temp = env_h[key];
		while ((key = ft_strcmp(args[1], temp->var_name)) && temp->next)
			temp = temp->next;
		if (key == 0)
			reset_variable(temp, args[2]);
		else
		{
			temp->next = new_hash_node_2(args[1], args[2]);
			set_list_end(temp->next, env_h);
		}
	}
	return (free_args(args));
}

void	free_thlist(t_hlist *node)
{
	free(node->var_name);
	free(node->contents);
	free(node);
}

int	unset_env_error(void)
{
	write(1, "unsetenv: Too few arguments.\n", 29);
	return (1);
}

void	delete_node(t_hlist *temp, t_hlist **env_h)
{
	if(temp->last && temp->next_2)
	{
		temp->last->next_2 = temp->next_2;
		temp->next_2->last = temp->last;
	}
	else if (temp->last)
		temp->last->next_2 = NULL;
	else if (temp->next_2)
		temp->next_2->last = NULL;
	if (env_h[HASH_SIZE] == temp)
		env_h[HASH_SIZE] = temp->next_2;
	if (env_h[HASH_SIZE + 1] == temp)
		env_h[HASH_SIZE + 1] = temp->last;
}

int	unset_env(char *str, t_hlist **env_h)
{
	t_hlist *temp;
	t_hlist *last;
	char	**args;
	int	i = 0;

	args = ft_strsplit(str, ' ');
	if (!args[1])
		return (free_args(args) && unset_env_error());
	while (args[++i])
	{
		temp = env_h[get_key(args[i])];
		last = temp;
		while (temp && ft_strcmp(temp->var_name, args[i]) && (last = temp))		
			temp = temp->next;
		if (temp)
		{
			delete_node(temp, env_h);
			if (last != temp)
				last->next = temp->next;
			else
				env_h[get_key(args[i])] = temp->next;
			free_thlist(temp);
		}
	}
	return (free_args(args));
}
