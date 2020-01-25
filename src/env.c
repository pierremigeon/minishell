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

int	set_env(char *str, t_hlist **env_h)
{
	t_hlist *temp;

	str += 6;
	while (*str == ' ')
		str++;
	if (*str == '\0')
		env(env_h);	
	return (1);
}

void	free_thlist(t_hlist *node)
{
	free(node->var_name);
	free(node->contents);
	free(node);
}

int	unset_env(char *str, t_hlist ***env_h)
{
	t_hlist *temp;
	t_hlist *last;
	char	**args;
	int	i;

	args = ft_strsplit(str, ' ');
	i = 1;
	while (args[i])
	{
		temp = *env_h[get_key(args[i])];
		last = temp;
		while (temp && ft_strcmp(temp->var_name, args[i]) && (last = temp))		
			temp = temp->next;
		if (temp)
		{
			if (last != temp)
				last->next = temp->next;
			else
				*env_h[get_key(*args)] = temp->next;
			free_thlist(temp);
		}
		i++;
	}
	free_args(args);
	return (1);
}
