

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"

typedef	struct		s_hlist
{
	char 		*var_name;
	char		*contents;
	int		var_len;
	int		con_len;
	struct s_hlist 	*next;
}			t_hlist;

#endif
