
# Pierre's Minishell Project

### As Beautiful as a Shell...

This is the 42 project Minishell! The instructions are to build a shell that reads commands from a user and executes them. Several Shell builtins are required. The shell can also execute binaries available through the users path, and fork new processes to do so.

To check out my shell:

1. clone repository
2. run `make` (places copy of minishell in /usr/local/bin/)
3. run `minishell` to launch the shell.
4. Typical commands can be used, as in a normal shell.

## Project requirements:

1. Create a UNIX command interpreter
2. Displays a prompt "&> " while waiting for command
3. After the user presses the return key, the command is executed if it is either in the user's path or if it is one of the shell built ins.
4. Shell builtins include: echo, cd, setenv, unsetenv, env, exit. I also included quit.
5. You must handle expansions for ~ and $.
6. If the command is not found, then an approriate error message is displayed.
7. The prompt is again displayed and waits for input from the user.


## Built-ins Usage:
Built-ins run within the shell without forking a new process.

**echo** 

 `echo [-n] [string ...]`

prints string to standard out. Use -n to exclude the newline.


**cd** 

`cd [directory]`

changes current working directory to the specified directory. If no directory is specified, defaults to $HOME


**env** 

`env`

prints out environmental variable names and their values.


**setenv** 

`setenv [var_name] [value]`

set environmental variable. With no input, same as calling env.


**unsetenv** 

`unsetenv var_1_name [var_2_name ...]`

delete environmental variables. 


## Relevant Features:
Environmental Variables are stored in a hash table. The nodes for each of the variables includes information about the length of the variable name and its contents for the sake of memory allocation during $ and ~ expansions. In this way, the time it takes to locate the variable is reduced, and the time it takes to expand the variable is also reduced due to having previously calculated string lengths. Obviously, this is a pretty minor speed up unless you were to have substantially more variables with extremely long names / stored values. However, I enjoy building hash tables and playing with linked lists. The order of placement into the hash table is maintained by linking each node through a second *next pointer, which is iterated through by the env builtin. This forms a doubly linked list. Pointers to the head and tail of the doubly linked list are stored in the last two sots (respectively) of the lookup table, allowing addition of new nodes to the end of the list without list transversal. In cases that environmental variables are deleted using unsetenv, entries are found in the hash table via lookup, and node deletion from the ordered list is facilitated due to the doubly linked structure (tranversal of the list to find the prior and subsequent nodes not necessary).

The echo built-in generally matches the behavior of UNIX echo. That is, it takes the -n parameter, and it ignores quotes (single or double). In the case that string contains opening quotation marks that are unmatched by closing marks, echo will take multi-line input until a closing quotation mark is included. 



