#include "../includes/minishell.h"

/* ERROR FUNCTIONS MODULE */

void    read_error(void)
{
        write(1, "Read error!\n", 12);
        exit (1);
}

void    no_such_command(char *str)
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

int	set_env_error(char **args)
{
	free_args(args, 0);
	write(1, "setenv: Too many arguments.\n", 28);
	return (1);
}

int	illegal_char_error(char **args, int i)
{
	if (i)
		free_args(args, 0);
	else
		free(*args);
	write(1, "setenv: Variable name must contain alphanumeric characters.\n", 60);
	return (1);
}

int	start_error(char **args, int i)
{
	if (i)
		free_args(args, 0);
	else
		free(*args);
	write(1, "setenv: Variable name must begin with a letter.\n", 48);
	return (1);
}

int	usage_statement_error(char **args)
{
	free_args(args, 0);
	write(1, "usage: setenv [variable_name] [value] | [-h]\n", 45);
	return (1);
}

int	quotation_error(int i)
{
	if (i == -1)
		write(1, "Unmatched \'\"\'.\n", 15);
	if (i == -2)
		write(1, "Unmatched \'\'\'.\n", 15);
	return (1);
}

int	unset_env_error(void)
{
	write(1, "unsetenv: Too few arguments.\n", 29);
	return (1);
}
