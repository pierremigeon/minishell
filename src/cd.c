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
	t_hlist *ptr;

	key = get_key("HOME");
	ptr = env_h[key];
	while (ptr->next != NULL)
	{
		if(!(ft_strcmp(ptr->var_name, "HOME")))
			return ((const char *)ptr->contents);
		ptr = ptr->next;
	}
	return ((const char *)ptr->contents);
}

char	*trim_begin(char *str)
{
	while (*str == ' ')
		str++;
	str += 2;
	while (*str == ' ')
		str++;
	return str;
}

int	cd(char *str, t_hlist **env_h)
{
	char *tmp;

	str = trim_begin(str);
	if (!*str) {
		chdir(get_tilde(env_h));
		return(1);
	}
	if ((tmp = ft_strchr(str, ' ')))
		*tmp = '\0';
	if(chdir((const char *)str))
		cd_error(str);
	return (1);
}
