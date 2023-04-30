#include "../includes/minishell.h"

int	test_dir(char *prog, char *path)
{
	DIR 		*dirp;
	struct dirent	*dp;

	if (ft_strcmp(".", prog) == 0 || ft_strcmp("..", prog) == 0)
		return (0);
	if (!(dirp = opendir(path)))
		return (0);
	while ((dp = readdir(dirp)))
	{
        	if (ft_strcmp(dp->d_name, prog) == 0) 
		{
			closedir(dirp);
			return (1);
		}
	}
	closedir(dirp);
	return (0);
}

char	*first_name(char *str)
{
	char *out;
	char *ptr;

	while (*str && *str == ' ')
		str++;
	ptr = ft_strchr(str, ' ');
	if (ptr)
		*ptr = '\0';
	out = ft_strdup(str);
	if (ptr)
		*ptr = ' ';
	return (out);
}

char	*in_path(char *str, t_hlist **env_h)
{
	t_hlist *temp;
	char 	**paths;
	char 	*program;
	int	i, x;

	i = 0;
	program = first_name(str);
	temp = env_h[get_key("PATH")];
	while (temp && ft_strcmp(temp->var_name, "PATH"))
		temp = temp->next;
	if (!temp)
		return (no_path_variable(program));
	paths = ft_strsplit(temp->contents, ':');
	while (paths[i])
		if ((x = test_dir(program, paths[i++])))
			return(free_all_ret_one(paths, program, --i));
	free_args(paths, 0);
	free(program);
	return (NULL);
}

char	*get_total_path(char *b_path, char *exec)
{
	char	*out;
	char	*ptr;
	int	i;

	i = ft_strlen(b_path);
	if (b_path[--i] == '/')
	{
		out = ft_strjoin(b_path, exec);
		free(b_path);
		return (out);
	}
	else
	{
		out = ft_strjoin_free(b_path, exec, '/');
		return (out);
	}
	return (NULL);
}

void	fork_process(char *str, char **env, char *b_path)
{
	pid_t	pid;
	char	*total_path;
	char 	**args;

	args = ft_strsplit(str, ' ');
	total_path = get_total_path(b_path, args[0]);
	pid = fork();
	if (pid == 0)
		execve(total_path, args, env);
	else if (pid > 0)
		wait(NULL);
	else
		ft_putstr("Error: Forking failed... \n");
	free_args(args, 0);
	free(total_path);
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

int	built_in(char *str, t_hlist **env_h)
{
	if (equal_wspace(str, "echo ", 4))
		return (echo_0(str));
	if (equal_wspace(str, "cd ", 2))
		return (cd(str, env_h));
	if (equal_wspace(str, "setenv ", 6))
		return (set_env(str, env_h));
	if (equal_wspace(str, "unsetenv ", 8))
		return (unset_env(str, env_h));
	if (equal_wspace(str, "env ", 3))
		return (env(env_h));
	if (equal_wspace(str, "exit ", 4) || equal_wspace(str, "quit ", 4))
		exit(0);
	if (equal_wspace(str, "H ", 3))
		return (history(env_h));
	return (0);
}

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
		while(ptr && *ptr != ' ' && *ptr != '\0')
			ptr++;
		str = (ptr) ? ptr + 1 : ptr;
	}
	return (0);
}

void	run_command(char **str, t_hlist **env_h, char **environ)
{
	char *exec_path;

	if (expandable(*str)) 
		*str = expand_command(*str, env_h);
	if (!(built_in(*str, env_h)))
	{
		if ((exec_path = in_path(*str, env_h)))
			fork_process(*str, environ, exec_path);
		else
			 no_such_command(*str);
	}
}

void	clear_terminal_at_start(t_hlist **env_h, char **environ) 
{
	char *str = "clear";
	run_command(&str, env_h, environ);
}

int	main()
{
	char 		*line;
	char		*line2 = NULL;
	extern char 	**environ;
	t_hlist		*env_h[HASH_SIZE + 1] = { NULL };
	int		i;

	get_env(env_h, environ);
	clear_terminal_at_start(env_h, environ);
	ft_putstr("$> ");
	while ((i = get_next_line(0, &line)) > 0)
	{
		if (*line && ft_strcmp("H", line))
			run_command(&line, env_h, environ);
		ft_putstr("$> ");
		if (!ft_strcmp("H", line) && line2 && ft_strcmp("H", line2))
		{
			ft_putstr(line2);
			write(1, "\n", 1);
			run_command(&line2, env_h, environ);
			ft_putstr("$> ");
		}
		if (ft_strcmp("H", line))
		{
			if(line2)
				free(line2);
			line2 = line;
		}
		set_history(line, env_h);
	}
	free_env(env_h);
	if (i < 0)
		read_error();
	return (0);
}
