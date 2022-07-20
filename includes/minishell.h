

#ifndef MINISHELL_H
# define MINISHELL_H

#define HASH_SIZE 50

#include "../libft/libft.h"
#include <sys/wait.h>
#include <dirent.h>
#include <stdio.h>

typedef	struct		s_hlist
{
	char 		*var_name;
	char		*contents;
	int		var_len;
	int		con_len;
	struct s_hlist 	*next;
	struct s_hlist 	*next_2;
	struct s_hlist	*last;
}			t_hlist;

//main Module
void		trim_end3(char **str);


//ENV BUILTINS MODULE
int             env(t_hlist **env_h);
int		env_2(t_hlist **env_h);
int             set_env(char *str, t_hlist **env_h);
void            free_thlist(t_hlist *node);
int             unset_env(char *str, t_hlist **env_h);
// ECHO MODULE
void		putnendl(char *str, char c, int mode, int *counts[3]);
int		q_balanced(char *str, char c, int *counts[3]);
void		echo_1(char *str, int n, char c);
char		check_quotes(char *o_str);
int		echo_0(char *str);
// CD MODULE
void		cd_error(char *str);
const char 	*get_tilde(t_hlist **env_h);
int		cd(char *str, t_hlist **env_h);
char    	*trim_begin(char *str);
// 
int		get_key(char *str);
void		read_error(void);
// COMMAND EXPANSION MODULE
int		run_case_2(t_hlist **env_h);
int		run_case_1(t_hlist **env_h, char *str, int *len);
int		case_1(char *str);
int		length_of_out(char *str, t_hlist **env_h);
char		*trim_end(char *str);
int		is_signal(char *str, int i);
char		*get_val_tilde(t_hlist **env_h);
char		*get_val(t_hlist **env_h, char *str);
char		*expand_command(char *str, t_hlist **env_h);
//HASH TABLE MODULE
t_hlist		*new_hash_node(char *env);
t_hlist 	*new_hash_node_2(char *variable, char *contents);
char 		*get_home(t_hlist **env_h);
void		add_tilde(t_hlist **env_h);
void		add_$(t_hlist **env_h);
void		get_env(t_hlist	**env_h, char **env);
void		test_hash_table(t_hlist **env_h);
//FREE AND ERROR
int		free_args(char **args);

#endif
