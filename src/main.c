#include "../includes/minishell.h"

#define HASH_SIZE 50

void	read_error(void)
{
	write(1, "Read error!\n", 12);
	exit (1);
}

void	no_such_command(char *str)
{
	char *space_ptr;

	while (*str == ' ')
		str++;
	if ((space_ptr = ft_strchr(str, ' ')))
		*space_ptr = '\0';
	ft_putstr("minishell: ");
	ft_putstr(str);
	ft_putstr(": command not found\n");
}

int	not_in_path(char *str, t_hlist **env_h)
{
	return (1);
	printf ("%s %s", str, env_h[0]->contents);
}

int	fork_process(char *str, t_hlist **env_h)
{
	pid_t	pid;

	if (not_in_path(str, env_h))
		return (1);
	pid = fork();
	if (pid == 0)
		;
	else if (pid > 0)
		;	
	else
		ft_putstr("Error: Forking failed... \n");
	return (0);
}

/*  cd module  */ 

int	get_key(char *str)
{
	if (*str == '~')
		return (ft_strlen("HOME") % HASH_SIZE);
	return (ft_strlen(str) % HASH_SIZE);
}

void	cd_error(char *str)
{
	char *space_ptr;

	while (*str == ' ')
		str++;
	if ((space_ptr = ft_strchr(str, ' ')))
		*space_ptr = '\0';
	ft_putstr("minishell: cd: ");
	ft_putstr(str);
        ft_putstr(": No such file or directory\n");
}

const char *get_tilde(t_hlist **env_h)
{
	int key;

	key = get_key("HOME");
	while (env_h[key]->next != NULL)
	{
		if(!(ft_strcmp(env_h[key]->var_name, "HOME")))
			return ((const char *)env_h[key]->contents);
		env_h[key] = env_h[key]->next;
	}
	return ((const char *)env_h[key]->contents);
}

int	cd(char *str, t_hlist **env_h)
{
	while (*str == ' ')
		str++;
	str += 2;
	while (*str == ' ')
		str++;
	if (!*str)
		chdir(get_tilde(env_h));
	else if(chdir((const char *)str))
		cd_error(str);
	return (1);
}

/* Echo Module */

void	putnendl(char *str, char c, int mode)
{
	while (*str == ' ')
		str++;
	str += 5;
	while (*str == ' ')
        	str++;
	if (mode)
	{
		str += 3;
		while (*str == ' ')
			str++;
	}
	while (*str)
	{
		if (*str != c)
			write(1, str, 1);
		str++;
	}
	if (mode == 0)
		write(1, "\n", 1);
}

char	get_ptr(char *str)
{
	char *ptr1;
	char *ptr2;

	ptr1 = ft_strchr(str, '\'');
	ptr2 = ft_strchr(str, '"');
	if (ptr1 && ptr2)
		return ((ptr1 < ptr2) ? *ptr1 : *ptr2);
	return ((ptr1) ? *ptr1 : *ptr2);
}

int	q_balanced(char *str, char c)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return ((count + 1) % 2);
}

void	echo_1(char **str, int n)
{
	char *ptr2, *str2;
	char c;
	int	i;

	i = 0;
	c = get_ptr(*str);
	if (q_balanced(*str, c))
		putnendl(*str, c, n);
	else 
	{
		while (write(1, ">", 1) && ((i = get_next_line(0, &str2)) > 0))
		{
			*str = ft_strjoin_free(*str, str2);
			free(str2);
			if (q_balanced(*str, c))
				break;
		}
		putnendl(*str, c, n);
	}
	if (i == -1)			
		read_error();
}

int	echo_0(char **str)
{
	char *ptr;
	int 	n;

	n = ((ptr = ft_strstr(*str, " -n "))) ? 1 : 0;
	if ((ptr = ft_strchr(*str, '\'')) || (ptr = ft_strchr(*str, '"')))
		echo_1(str, n);
	else if (n)
		putnendl(*str, 0, n);
	else
		putnendl(*str, 0, n);
	return (1);
}

/*  End Echo module  */

int	equal_wspace(char *str1, char *str2, size_t len)
{
	while (*str1 == ' ')
		str1++;
	if (ft_strncmp(str1, str2, len) == 0 && *(str1 + len) == '\0')
		return (1);
	if (ft_strncmp(str1, str2, len + 1) == 0)
		return (1);
	return (0);
}

int	built_in(char **str, t_hlist **env_h)
{
	if (equal_wspace(*str, "echo ", 4))
		return (echo_0(str));
	if (equal_wspace(*str, "cd ", 2))
		return (cd(*str, env_h));
	if ((strcmp(*str, "setenv")) == 0)
		;
	if ((strcmp(*str, "unsetenv")) == 0)
		;
	if ((strcmp(*str, "env")) == 0)
		;
	if (equal_wspace(*str, "exit ", 4) || equal_wspace(*str, "quit ", 4))
		exit(0);
	return (0);
}

/*
 	Handling expansions- ultimately store the lengths of everything in a hash table 
	so that you don't have to calculate the length of these strings each time you 
	have to run expansions. 
*/

int	length_of_out(char *str, t_hlist **env_h)
{
	int 	len[3] = { 0 };
	t_hlist *temp;
	char 	*ptr;

	while (*(str + len[0]))
	{
		if ((*(str + len[0]) == '$') || (*(str + len[0]) == '~'))
		{
			if (*(str + len[0]) == '$')
				++len[0];
			if (!(ptr = ft_strchr(str + len[0], ' ')) && (len[2] = 1))
				ptr = ft_strchr(str + len[0], 0);
			*ptr = '\0';
			temp = env_h[get_key(str + len[0])];
			while (ft_strcmp(temp->var_name, str + len[0]))
				temp = temp->next;
			len[1] += temp->con_len - temp->var_len;
			if (len[2] == 0)
				*ptr = ' ';
		}
		len[2] = 0;
		++len[0];
	}
	return (len[1]);
}

void	expand_command(char **str, t_hlist **env_h)
{
	char *out;
	int i;

	i = length_of_out(*str, env_h);
	printf ("The size is calculated to be %i\n", i);
/*
	if(!(out = (char *)malloc(sizeof(char) * ++i)))
		exit(1);
	while (*(*str + i))
	{
		if (*(*str + i) == '~')
			while ()
		else
			
		i++;
	}
	printf ("%s %s", *str, *env);
*/
}

void	run_command(char **str, t_hlist **env_h)
{
	int	status;

	status = 0;
	expand_command(str, env_h);
	if (!(built_in(str, env_h)))
		status = fork_process(*str, env_h);
	if (status)
		no_such_command(*str);
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
	new->con_len = ft_strlen(env) + 1;
	new->var_len = ft_strlen(ptr + 1);
	*ptr = '=';
	new->next = NULL;
	return (new);
}

char *get_home(t_hlist **env_h)
{
	t_hlist *temp;
	char *out;

	temp = env_h[get_key("~")];
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
		temp = new_hash_node("~");
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_hash_node(home);
	}
	free(home);
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

int	main()
{
	char 		*line;
	extern char 	**environ;
	t_hlist		*env_h[HASH_SIZE] = { NULL };
	int		i;

	get_env(env_h, environ);
	//test_hash_table(env_h);
	ft_putstr("$> ");
	while ((i = get_next_line(0, &line)) > 0)
	{
		if (*line)
			run_command(&line, env_h);
		ft_putstr("$> ");
		free(line);
	}
	//free_everything(env_h);
	if (i < 0)
		read_error();
	return (0);
}
