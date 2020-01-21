#include "minishell.h"

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

int	echo(char *str)
{
	char word[] = "echo ";
	char *ptr;
	char *str2;
	int	i;

	i = 0;
	while(*str && word[i] && *str == word[i])
	{
		str++;
		++i;
	}
	if (*str == '"' || *str == '\'')
		str++;
	if ()
	if ((ptr = ft_strrchr(str, '"')))
		*ptr = '\0';
	else if ((ptr = ft_strrchr(str, '\'')))
		*ptr = '\0';
	ft_putendl(str);
	if (ptr != NULL)
		*ptr = '"';
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

int	built_in(char *str)
{
	if (equal_wspace(str, "echo ", 4))
		return (echo(str));
	if ((strcmp(str, "cd")) == 0)
		;
	if ((strcmp(str, "setenv")) == 0)
		;
	if ((strcmp(str, "unsetenv")) == 0)
		;
	if ((strcmp(str, "env")) == 0)
		;
	if (equal_wspace(str, "exit ", 4) || equal_wspace(str, "quit ", 4))
		exit(0);
	return (0);
}

void	expand_command(char *str, char **env)
{
	return ;
	printf ("%s %s", str, *env);
}

void	run_command(char *str, char **env)
{
	int	status;

	status = 0;
	expand_command(str, env);
	if (!(built_in(str)))
		status = fork_process(str, env);
	if (status)
		no_such_command(str);
}

int	main()
{
	char 		*line;
	extern char 	**environ;

	ft_putstr("$> ");
	while (get_next_line(0, &line))
	{
		if (*line)
			run_command(line, environ);
		ft_putstr("$> ");
		free(line);
	}
	return (0);
}
