#include "../includes/minishell.h"

void	free_thlist(t_hlist *node)
{
	free(node->var_name);
	free(node->contents);
	free(node);
}

int	free_args(char **args, int arg_len)
{
	int i;

	i = 0;
	while (i < arg_len || args[i])
		free (args[i++]);
	free(args);
	return (1);
}

char	*free_all_ret_one(char **paths, char *program, int i)
{
	int x;
	char *out;

	x = 0;
	while (paths[x])
	{
		if (x == i)
			out = ft_strdup(paths[x]);	
		free(paths[x]);
		++x;
	}
	free(paths);
	free(program);
	return (out);
}

void	free_env(t_hlist **env_h)
{
	int n;
	t_hlist *temp;
	t_hlist *last;

	n = 0;
	while (n < HASH_SIZE + 2)
	{
		temp = env_h[n];
		while(temp)
		{
			last = temp;
			temp = temp->next;
			free_thlist(last);
			last = NULL;
		}
		++n;
	}
}

void	f_out(char **str)
{
	free(*str);
	*str = NULL;
}

char    *no_path_variable(char *program)
{
	free(program);
	return (NULL);
}
