
/* ENV HASH TABLE MODULE */

#include "../includes/minishell.h"

t_hlist *new_hash_node(char *env)
{
	t_hlist *new;
	char *ptr;

        if(!(new = (t_hlist *)malloc(sizeof(t_hlist))))
		exit(1);
	ptr = ft_strchr(env, '=');
	*ptr = '\0';
	new->var_name = ft_strdup(env);
	new->contents = ft_strdup(ptr + 1);
	new->con_len = ft_strlen(ptr + 1);
	new->var_len = ft_strlen(env) + 1;
	*ptr = '=';
	new->next = NULL;
	return (new);
}

char *get_home(t_hlist **env_h)
{
	t_hlist *temp;
	char *out;

	temp = env_h[get_key("HOME")];
	while (ft_strcmp(temp->var_name, "HOME"))
		temp = temp->next;
	out = ft_strjoin("~=", temp->contents);
	return (out);
}

void	add_tilde(t_hlist **env_h)
{
	t_hlist *temp;
	char *home;

	home = get_home(env_h);
	temp = env_h[get_key("~")];
	if (temp == NULL)
		temp = new_hash_node(home);
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_hash_node(home);
	}
	free(home);
}

//Figure out the casting stuff and test before deploying this function :)
void	add_$(t_hlist **env_h)
{
	t_hlist *temp;
	char 	*pid;
	char	*ptr;

	pid = ft_itoa((size_t)getpid());
	ptr = pid;
	temp = env_h[get_key(pid)];
	pid = ft_strjoin("$=", pid);
	free(ptr);
        if (temp == NULL)
                temp = new_hash_node(pid);
        else    
        {       
                while (temp->next)
                        temp = temp->next;
                temp->next = new_hash_node(pid);
        }
        free(pid);
}

void	get_env(t_hlist	**env_h, char **env)
{
	int 	n;
	int	key;
	char 	*ptr;
	t_hlist *temp;

	n = -1;
	while (env[++n])
	{
		ptr = ft_strchr(env[n], '=');
		*ptr = '\0';
		key = get_key(env[n]);
		*ptr = '=';
		if (env_h[key] == NULL)
			env_h[key] = new_hash_node(env[n]);
		else
		{
			temp = env_h[key];
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new_hash_node(env[n]);
		}	
	}
	add_tilde(env_h);
	//add_$(env_h);
}

void	test_hash_table(t_hlist **env_h)
{
	int n;

	n = 0;
	while (n < HASH_SIZE)
	{
		while (env_h[n] != NULL)
		{
			printf ("%i is the index and %s is the name \n", n, env_h[n]->var_name);
			env_h[n] = env_h[n]->next;
		}
		++n;
	}
	exit (0);
}
