#include "../includes/minishell.h"

void	read_error(void)
{
	write(1, "Read error!\n", 12);
	exit (1);
}

void	no_such_command(char *str)
{
	ft_putstr("minishell: ");
	ft_putstr(str);
	ft_putstr(": command not found\n");
}

int	not_in_path(char *str, char **env)
{
	return (1);
	printf ("%s %s", str, *env);
}

int	fork_process(char *str, char **env)
{
	pid_t	pid;

	if (not_in_path(str, env))
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

void	echo_1(char **str)
{
	char *ptr1, *ptr2, *str2;
	int	i;

	i = 0;
	if ((*(*str + 5) == '"' || *(*str + 5) == '\'') && (ptr1 = (*str + 5)))
	{
		if ((ptr2 = ft_strrchr((*str + 6), *ptr1)))
		{
			*ptr2 = '\0';
			ft_putendl(*str + 6);
			return;
		}
		else
		{
			while ((write(1, ">", 1) && (i = get_next_line(0, &str2)) > 0) && (*str = ft_strjoin_free(*str, str2)) && !(ptr2 = ft_strrchr(*str + 6, *ptr1)))
				free(str2);
			*ptr2 = '\0';
			ft_putendl(*str + 6);
			free(str2);
		}
		if (i == -1)
			read_error();
	}
	else
		ft_putendl(*str + 5);
}

int	echo_0(char **str)
{
	char *ptr;
	
	if ((ptr = ft_strchr(*str, '\'')) || (ptr = ft_strchr(*str, '"')))
		echo_1(str);
	else
		ft_putendl(*str + 5);
	return (1);
}

int	equal_wspace(char *str1, char *str2, size_t len)
{
	if (ft_strncmp(str1, str2, len) == 0 && *(str1 + len) == '\0')
		return (1);
	if (ft_strncmp(str1, str2, len + 1) == 0)
		return (1);
	return (0);
}

int	built_in(char **str)
{
	if (equal_wspace(*str, "echo ", 4))
		return (echo_0(str));
	if ((strcmp(*str, "cd")) == 0)
		;
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

void	expand_command(char **str, char **env)
{
	return ;
	printf ("%s %s", *str, *env);
}

void	run_command(char **str, char **env)
{
	int	status;

	status = 0;
	expand_command(str, env);
	if (!(built_in(str)))
		status = fork_process(*str, env);
	if (status)
		no_such_command(*str);
}

int	main()
{
	char 		*line;
	extern char 	**environ;
	int		i;

	ft_putstr("$> ");
	while ((i = get_next_line(0, &line)))
	{
		if (*line)
			run_command(&line, environ);
		ft_putstr("$> ");
		free(line);
	}
	if (i < 0)
		read_error();
	return (0);
}
