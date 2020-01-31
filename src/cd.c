#include "../includes/minishell.h"

/* CD BUILTIN MODULE */

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
