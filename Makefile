



all:
	@make -C libft
	@echo "Compiling to executable and copying to path!"
	@gcc ./src/main.c ./libft/libft.a -o minishell
	@chmod +x ./minishell
	@cp ./minishell /usr/local/bin/minishell

test:
	@echo "Compiling for testing with lldb"
	@gcc -g main.c ./libft/libft.a -o minishell	

edit:
	vi ./src/main.c

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
