

#ifndef MINISHELL_H
# define MINISHELL_H

#define HASH_SIZE 50

#include "../libft/libft.h"
#include <sys/wait.h>

typedef	struct		s_hlist
{
	char 		*var_name;
	char		*contents;
	int		var_len;
	int		con_len;
	struct s_hlist 	*next;
}			t_hlist;

// ECHO MODULE
void		putnendl(char *str, char c, int mode);
char		get_ptr(char *str);
int		q_balanced(char *str, char c);
void		echo_1(char *str, int n);
int		echo_0(char *str);
// CD MODULE
void		cd_error(char *str);
const char 	*get_tilde(t_hlist **env_h);
int		cd(char *str, t_hlist **env_h);
// 
int		get_key(char *str);
void		read_error(void);
// COMMAND EXPANSION MODULE
int		run_case_2(t_hlist **env_h);
int		run_case_1(t_hlist **env_h, char *str, int *len);
int		case_1(char *str);
int		length_of_out(char *str, t_hlist **env_h);
char		*trim_end(char *str);
int		is_signal(char *str);
char		*get_val_tilde(t_hlist **env_h);
char		*get_val(t_hlist **env_h, char *str);
char		*expand_command(char *str, t_hlist **env_h);
//HASH TABLE MODULE
t_hlist		*new_hash_node(char *env);
char 		*get_home(t_hlist **env_h);
void		add_tilde(t_hlist **env_h);
void		add_$(t_hlist **env_h);
void		get_env(t_hlist	**env_h, char **env);
void		test_hash_table(t_hlist **env_h);


#endif
