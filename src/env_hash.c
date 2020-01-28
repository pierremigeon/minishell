
/* ENV HASH TABLE MODULE */

#include "../includes/minishell.h"

t_hlist *new_hash_node_2(char *variable, char *contents)
{
	t_hlist *new;
	char *ptr;

	if(!(new = (t_hlist *)malloc(sizeof(t_hlist))))
		exit(1);
        new->var_name = ft_strdup(variable);
	new->var_len = ft_strlen(variable) + 1;
        new->contents = ft_strdup(contents);
        new->con_len = ft_strlen(contents);
        new->next = NULL;
	new->next_2 = NULL;
        return (new);
}

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
	new->next_2 = NULL;
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

int	wrap_get_key(char *str)
{
	int key;
	char *ptr;

	ptr = ft_strchr(str, '=');
	*ptr = '\0';
	key = get_key(str);
	*ptr = '=';
	return (key);
}

void	add_extras(t_hlist **env_h)
{
	add_tilde(env_h);
	add_$(env_h);
}

void	make_links(t_hlist **last, t_hlist **temp)
{
	if (*last == NULL)
		*last = *temp;
	else
	{
		(*last)->next = *temp;
		*last = (*last)->next_2;
	}
}

void	get_env(t_hlist	**env_h, char **env)
{
	int 	n;
	int	key;
	t_hlist *temp;
	t_hlist	*last = NULL;

	n = -1;
	env_h[HASH_SIZE] = env_h[wrap_get_key(env[0])];
	while (env[++n])
	{
		key = wrap_get_key(env[n]);
		if (env_h[key] == NULL)
		{
			env_h[key] = new_hash_node(env[n]);
			temp = env_h[key];
		}
		else
		{
			temp = env_h[key];
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new_hash_node(env[n]);
			temp = temp->next_2;
		}
		make_links(&last, &temp);
	}
	add_extras(env_h);
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
