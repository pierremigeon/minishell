#include "../includes/minishell.h"


int	env_2(t_hlist **env_h)
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

int	env(t_hlist **env_h)
{
	int 	n;
	t_hlist *temp;

	n = 0;
	while (n < HASH_SIZE)
	{
		temp = env_h[n];
		while (temp)
		{
			ft_putstr(temp->var_name);
			ft_putchar('=');
			ft_putendl(temp->contents);
			temp = temp->next;
		}
		++n;
	}
	return (1);
}

int	set_env_error(void)
{
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

	len = 4;
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

int	set_env(char *str, t_hlist **env_h)
{
	t_hlist *temp;
	char 	**args;
	int	key;

	args = ft_strsplit(str, ' ');
	if ( args_len(args) == 1 || args_len(args) == 4)
		return (args_len(args) == 4) ? free_args(args) && set_env_error() : free_args(args) && env(env_h);
	if (!args[2])
		args = surgery(args);
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
