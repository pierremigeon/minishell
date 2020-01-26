#include "../includes/minishell.h"

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

int	set_env(char *str, t_hlist **env_h)
{
	t_hlist *temp;
	char 	**args;
	int	key;

	args = ft_strsplit(str, ' ');
	if (!args[1] || args[3])
		return ((args[3]) ? free_args(args) && set_env_error() : free_args(args) && env(env_h));
	if (!args[2])
		args[2] = ft_strdup("");
	key = get_key(args[1]);
	if (!env_h[key])
		env_h[key] = new_hash_node_2(args[1], args[2]);
	else
	{
		temp = env_h[key];
		while ((key = ft_strcmp(args[1], temp->var_name)) && temp->next)
			temp = temp->next;
		if (key == 0)
			reset_variable(temp, args[2]);
		else
			temp->next = new_hash_node_2(args[1], args[2]);
	}
	free_args(args);
	return (1);
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

int	unset_env(char *str, t_hlist **env_h)
{
	t_hlist *temp;
	t_hlist *last;
	char	**args;
	int	i;

	args = ft_strsplit(str, ' ');
	i = 1;
	if (!args[1])
		return (free_args(args) && unset_env_error());
	while (args[i])
	{
		temp = env_h[get_key(args[i])];
		last = temp;
		while (temp && ft_strcmp(temp->var_name, args[i]) && (last = temp))		
			temp = temp->next;
		if (temp)
		{
			if (last != temp)
				last->next = temp->next;
			else
				env_h[get_key(*args)] = temp->next;
			free_thlist(temp);
		}
		i++;
	}
	return (free_args(args));
}
