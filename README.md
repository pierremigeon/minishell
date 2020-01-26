
# Pierre's Minishell Project

### As Beautiful as a Shell...

This is the 42 project Minishell! The instructions are to build a shell that reads commands from a user and executes them. Several Shell builtins are required. The shell can also execute binaries available through the users path, and fork new processes to do so.

To check out my shell:

1. clone repository
2. run `make` (places copy of minishell in /usr/local/bin/)
3. run `minishell` to launch the shell.

## Project requirements:

1. Create a UNIX command interpreter
2. Displays a prompt "&> " while waiting for command
3. After the user presses the return key, the command is executed if it is either in the user's path or if it is one of the shell built ins.
4. Shell builtins include: echo, cd, setenv, unsetenv, env, exit. I also included quit.
5. You must handle expansions for ~ and $.
6. If the command is not found, then an approriate error message is displayed.
7. The prompt is again displayed and waits for input from the user.

## Project status:

I have nearly completed this project, but am developing the env builtins and cleaning up the remaining memory leaks. 
