#include "../includes/minishell.h"

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

int	in_path(char *str, t_hlist **env_h)
{
	return (0);
	printf ("%s %s", str, env_h[0]->contents);
}

int	fork_process(char *str, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		//execve(str, args, env_h);
		;
	}
	else if (pid > 0)
	{
		wait(NULL);
	}	
	else
		ft_putstr("Error: Forking failed... \n");
	return (0);
}

int	get_key(char *str)
{
	return (ft_strlen(str) % HASH_SIZE);
}

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
		return (echo_0(*str));
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

/* Main Flow control - would be better to check if it's a real command before expansions happen */

int	expandable(char *str)
{
	char *ptr;
	char *ptr2;

	ptr2 = str;
	while (str && *str)
	{
		if ((ptr = ft_strchr(str, '$')))
			if (*(ptr + 1) != ' ')
				return (1);
		str = (ptr) ? ptr + 1 : ptr;
	}
	str = ptr2;
	while (str && *str)
	{
		if ((ptr = ft_strchr(str, '~')))
			if (*(ptr + 1) == '/' || *(ptr + 1) == ' ' || *(ptr + 1) == '\0')
				return (1);
		str = (ptr) ? ptr + 1 : ptr;
	}
	return (0);
}


void	run_command(char **str, t_hlist **env_h, char **environ)
{
	if (expandable(*str))
		*str = expand_command(*str, env_h);
	if (!(built_in(str, env_h)))
	{
		if (in_path(*str, env_h))
			fork_process(*str, environ);
		else
			 no_such_command(*str);
	}
}

int	main()
{
	char 		*line;
	extern char 	**environ;
	t_hlist		*env_h[HASH_SIZE] = { NULL };
	int		i;

	get_env(env_h, environ);
	ft_putstr("$> ");
	while ((i = get_next_line(0, &line)) > 0)
	{
		if (*line)
			run_command(&line, env_h, environ);
		ft_putstr("$> ");
		free(line);
	}
	//free_everything(env_h);
	if (i < 0)
		read_error();
	return (0);
}
