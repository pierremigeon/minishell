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

int	built_in(char **str)
{
	if (equal_wspace(*str, "echo ", 4))
		return (echo_0(str));
	if (equal_wspace(*str, "cd", 2))
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
	while ((i = get_next_line(0, &line)) > 0)
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
