#include "../includes/minishell.h"

int	history(t_hlist **env_h)
{
	printf("%s\n", env_h[HASH_SIZE - 1]->var_name);

	return (1);
}
