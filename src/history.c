#include "../includes/minishell.h"

int	history(t_hlist **env_h, char **environ)
{
	t_hlist	*temp;
	char	*key_s = "history string";
	int	key_i;

	key_i = get_key(key_s);
	if (!env_h[key_i])
		return (1);
	temp = env_h[key_i];
	while ((key_i = ft_strcmp(key_s, temp->var_name)) && temp->next)
		temp = temp->next;
	if (temp)
	{	
		ft_putstr("$> ");
		ft_putstr(temp->contents);
		ft_putstr("\n");
		run_command(&temp->contents, env_h, environ);
	}
	return (1);
}

int	check_H(char *str)
{
	return (*str == 'H' && (*(str + 1) == '\0' || *(str + 1) == ' '));
}

void	set_history(char *str, t_hlist **env_h)
{
	t_hlist *temp;
	char    *key_s = "history string";
	int     key_i;

	if (check_H(str))
		return ;
	key_i = get_key(key_s);
	if (!env_h[key_i])
		new_point(env_h, key_i, key_s, str);
	else
	{
		temp = env_h[key_i];
		while ((key_i = ft_strcmp(key_s, temp->var_name)) && temp->next)
			temp = temp->next;
		if (key_i == 0)
			reset_variable(temp, str);
		else
		{
			temp->next = new_hash_node_2(key_s, str);
			set_list_end(temp->next, env_h);
		}
	}
}
