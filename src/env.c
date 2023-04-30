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
	free_args(args, 0);
	return (new_args);
}

void	new_point(t_hlist **env_h, int key, char *str1, char *str2)
{
	env_h[key] = new_hash_node_2(str1, str2);
	if (!env_h[HASH_SIZE] && !env_h[HASH_SIZE + 1])
	{
		env_h[HASH_SIZE] = env_h[key];
		env_h[HASH_SIZE + 1] = env_h[key];
	}
	else
		set_list_end(env_h[key], env_h);
}

int	isQorS(char c)
{
	return (c == '\"' || c == '\'' || c == '\\');
}

int	esc(int flag)
{
	return (flag % 2);
}

int	check_behind(char c, int *flag, char literal)
{
	if (!literal && c == '\\' && (*flag += 1))
		return (esc(*flag - 1));
	else if (c == '\\')
		return (1);
	if ((c == '\"' || c == '\'') && !esc(*flag))
		return ((*flag = 0));
	return (!(*flag = 0));
}

int	q_check(char *str, char c, int total)
{
	if (c == str[total] && !(str[total] = '\0'))
		return (0);
	if (str[total] && (c == '\"' || c == '\''))
		return (1);
	if (c == '\"' || c == '\'')
		str[total] = c;
	return (0);
}

char	*prepare_out(char *str, int count)
{
	int i;
	int x;
	int b_flag;
	char *out;

	i = -1;
	b_flag = x = 0;
	if (!(out = (char *)malloc(sizeof(char) * count--)))
		exit(1);
	out[count] = '\0';
	while (str[++i])
	{
		if (check_behind(str[i], &b_flag, out[count]))
			out[x++] = str[i];
		else if (q_check(out, str[i], count))
			out[x++] = str[i];
	}
	out[x] = '\0';
	return (out);
}

char	*trim_qs(int count, char *str, int flag)
{
	char *out;
	int i;
	int x;

	i = -1;
	x = 0;
	if (count == 0)
		return (str);
	if (flag * count == -4 && illegal_char_error(&str, 0))
		return (NULL);
	if (flag * count == -3 && start_error(&str, 0))
		return (NULL);
	if (count < 0 && quotation_error(count))
		return (NULL);
	out = prepare_out(str, count);
	free(str);
	return (out);
}

void	set_counts(char c, int *c1, int c3, int *length)
{
	int ca[2] = { -1, -2 };

	if (c == '\\')
		return;
	if (*c1 == 0 && !esc(c3))
		*c1 = ca[(int)c % 2];
	else if (*c1 == ca[(int)c % 2])
		*c1 = 0;
	else *length -= 1;
}

int	pross_bksl(char c, int *i, int c1)
{
	if (c1 != 0 && c == '\\')
		return (0);
	else if (c == '\\')
		return ((*i += 1));
	return (!esc(*i) * !(*i = 0));
}

int	illegal_c(char c, int flag)
{
	if (c == '\0')
		return (0);
	if (c == '\\')
		return (1);
	if (c == '.' && flag == 2)
		return (0);
	if (ft_isdigit(c) && flag == 2)
		return (0);
	if (!ft_isalpha(c) && c != '_' && !isQorS(c))
		return (1);
	return (0);
}

void	check_start_quotes(char *str, int i, int c1, int *c4)
{
	int c[2] = {-1, -2};
	int c4_status;

	c4_status = (*c4 == 0) ? 1 : 2;
	if (*c4 == -4 || *c4 == -3)
		return ;
	if (illegal_c(str[i], c4_status))
		if ((*c4 = *c4 - 3))
			return;
	if (c[str[i] % 2] == c1)
		if (str[i - 1] != str[i] || illegal_c(str[i + 1], c4_status))
			if ((*c4 = *c4 - 3))
				return;
}

int	set_x(int *alphabet_flag, int c1, char c)
{
	if (*alphabet_flag == 0 && c1 == 0)
		*alphabet_flag = -1;
	return (1);
}

int	return_decode(int total, int *x, int i, int flag)
{
	if (x[0] < 0)
		return (x[0]);
	if (x[3] < -1)
		return (x[3]);
	if (total == 0)
		return (0);
	return (i - total + 1);
}

int	count_qs(char *str, int flag)
{
	int i;
	int total;
	int x[4] = { 0, 0, 0, 0 };

	i = -1;
	total = 0;
	while(str[++i])
	{
		if (flag)
			check_start_quotes(str, i, x[0], &x[3]);
		if (isQorS(str[i]) || set_x(&x[3], x[0], str[i]) && (x[2] = 0))
			if (pross_bksl(str[i], &x[2], x[0]) && (total += 1))
				set_counts(str[i], &x[0], x[2], &total);
	}
	return (return_decode(total, x, i, flag));
}

char	**trimming(char **args, int ar_len)
{
	int i;
	int f;

	i = 0;
	f = (i == 1);
	while (++i < ar_len && ((f = (i == 1)) || 1))
		if (!(args[i] = trim_qs(count_qs(args[i], f), args[i], f)))
			if (free_args(args, ar_len))
				return (NULL);
	return (args);
}

char	**clean_args(char *str, t_hlist **env_h)
{
	char	**args;
	int	ar_len;

	args = ft_strsplit(str, ' ');
	if (args[1] != NULL && !(ft_strcmp(args[1], "-h")))
		if (usage_statement_error(args))
			return (NULL);
	ar_len = args_len(args);
	if (ar_len >= 4 && set_env_error(args))
		return (NULL);
	if (ar_len == 1 && free_args(args, 0) && env(env_h))
		return (NULL);
	if (ar_len == 2)
		args = surgery(args);
	return (trimming(args, ar_len));
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
	return (free_args(args, 0));
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
		return (free_args(args, 0) && unset_env_error());
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
	return (free_args(args, 0));
}
