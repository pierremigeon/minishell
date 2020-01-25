
SRC= ./src/main.c ./src/echo.c ./src/cd.c ./src/env_hash.c ./src/expansion.c

all:
	@make -C libft
	@echo "Compiling to executable and copying to path!"
	@gcc $(SRC) ./libft/libft.a -o minishell
	@chmod +x ./minishell
	@cp ./minishell /usr/local/bin/minishell

test:
	@echo "Compiling for testing with lldb"
	@gcc -g $(SRC) ./libft/libft.a -o minishell	

runtest:
	@lldb minishell

rt: test runtest

edit:
	vi ./src/main.c

edit_h:
	vi ./includes/minishell.h

clean:
	@echo "Cleaning up files"
	@rm ./minishell
	@if [ -e minishell.dSYM ]; then rm -rf minishell.dSYM; fi
	@echo "Cleaning up libft"
	@make clean -C libft

fclean:
	@echo "Cleaning up everything"
	@rm ./minishell
	@if [ -e minishell.dSYM ]; then rm -rf minishell.dSYM; fi
	@echo "Cleaning up libft"
	@make fclean -C libft

re: fclean all
