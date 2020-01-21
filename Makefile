



all:
	@echo "Compiling to executable and copying to path!"
	@gcc main.c ./libft/libft.a -o minishell
	@chmod +x ./minishell
	@cp ./minishell /usr/local/bin/minishell

test:
	@echo "Compiling for testing with lldb"
	@gcc -g main.c ./libft/libft.a -o minishell	

edit:
	vi main.c

clean:
	@echo "Cleaning up files"
	@rm ./minishell
	@if [ -e minishell.dSYM ]; then rm -rf minishell.dSYM; fi
