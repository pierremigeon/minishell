
SRC = ./src/main.c ./src/echo.c ./src/cd.c ./src/env_hash.c ./src/expansion.c ./src/env.c
LIB = ./libft/libft.a
OUT = minishell

all:
	@make -C libft
	@echo "Compiling to executable and copying to path!"
	@gcc $(SRC) $(LIB) -o $(OUT)
	@chmod +x ./$(OUT)
	@cp ./$(OUT) /usr/local/bin/$(OUT)

test:
	@echo "Compiling for testing with lldb"
	@gcc -g $(SRC) $(LIB) -o $(OUT)

runtest:
	@lldb $(OUT)

memcheck_1:
	@gcc -g $(SRC) $(LIB) -o $(OUT)
	@if [ -e valgrind_suppressions.sh ]; then bash valgrind_suppressions.sh $(OUT); fi 

memcheck_2:
	valgrind -v --leak-check=yes $(OUT)

rt: test runtest

edit:
	vi ./src/main.c

edit_e:
	vi ./src/echo.c

edit_c:
	vi ./src/cd.c	

edit_h:
	vi ./includes/minishell.h

clang:
	@clang $(SRC) $(LIB) -o $(OUT)
	@chmod +x ./$(OUT)
	@cp ./$(OUT) /usr/local/bin/$(OUT)

clangtest:
	@clang -g $(SRC) $(LIB) -o $(OUT)
	lldb ./minishell

run: all
	@./minishell	


clean:
	@echo "Cleaning up files"
	@rm ./$(OUT)
	@if [ -e $(OUT).dSYM ]; then rm -rf $(OUT).dSYM; fi
	@echo "Cleaning up libft"
	@make clean -C libft

fclean:
	@echo "Cleaning up everything"
	@rm ./$(OUT)
	@if [ -e $(OUT).dSYM ]; then rm -rf $(OUT).dSYM; fi
	@echo "Cleaning up libft"
	@make fclean -C libft

re: fclean all
