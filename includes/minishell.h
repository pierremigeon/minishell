#ifndef MINISHELL_H
# define MINISHELL_H
# define HASH_SIZE 50
# include "../libft/libft.h"
# include <sys/wait.h>
# include <dirent.h>
# include <stdio.h>

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

//MAIN MODULE
void			run_command(char **str, t_hlist **env_h, char **environ);

//ENV BUILTINS MODULE
int			env(t_hlist **env_h);
int			env_2(t_hlist **env_h);
int			set_env(char *str, t_hlist **env_h);
void			free_thlist(t_hlist *node);
int			unset_env(char *str, t_hlist **env_h);
void			reset_variable(t_hlist *node, char *contents);
void			new_point(t_hlist **env_h, int key, char *str1, char *str2);
void			set_list_end(t_hlist *new_end, t_hlist **env_h);

// ECHO MODULE
void			putnendl(char *str, char c, int mode);
char			get_ptr(char *str);
int			q_balanced(char *str, char c);
void			echo_1(char *str, int n);
int			echo_0(char *str);

// CD MODULE
void			cd_error(char *str);
const char 		*get_tilde(t_hlist **env_h);
int			cd(char *str, t_hlist **env_h);
char    		*trim_begin(char *str);
char    		*trim_end2(char *str); 
int			get_key(char *str);
void			read_error(void);

// COMMAND EXPANSION MODULE
int			run_case_2(t_hlist **env_h);
int			run_case_1(t_hlist **env_h, char *str, int *len);
int			case_1(char *str);
int			length_of_out(char *str, t_hlist **env_h);
char			*trim_end(char *str);
int			is_signal(char *str, int i);
char			*get_val_tilde(t_hlist **env_h);
char			*get_val(t_hlist **env_h, char *str);
char			*expand_command(char *str, t_hlist **env_h);

//HASH TABLE MODULE
t_hlist			*new_hash_node(char *env);
t_hlist 		*new_hash_node_2(char *variable, char *contents);
char 			*get_home(t_hlist **env_h);
void			add_tilde(t_hlist **env_h);
void			add_$(t_hlist **env_h);
void			get_env(t_hlist	**env_h, char **env);
void			test_hash_table(t_hlist **env_h);

//ERROR FUNCTIONS MODULE
int			free_args(char **args, int arg_len);
int			set_env_error(char **args);
int			illegal_char_error(char **args, int i);
int			start_error(char **args, int i);
int			usage_statement_error(char **args);
int			quotation_error(int i);
int			unset_env_error(void);
void			no_such_command(char *str);
void			read_error(void);

//FREE FUNCTIONS MODULE
void			free_thlist(t_hlist *node);
int			free_args(char **args, int arg_len);
char			*free_all_ret_one(char **paths, char *program, int i);
void			free_env(t_hlist **env_h);
void			f_out(char **str);
char			*no_path_variable(char *program);

//HISTORY FEATURE MODULE
int     		history(t_hlist **env_h, char **environ);
void    		set_history(char *str, t_hlist **env_h);


#endif
