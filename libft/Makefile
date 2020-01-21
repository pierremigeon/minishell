# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/10 16:09:15 by pmigeon           #+#    #+#              #
#    Updated: 2018/11/25 21:41:53 by pmigeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = *.c
HEADER = ./
LIBNAME = libft.a
COMPILER = gcc
FLAGS = -Wall -Werror -Wextra -c
OFILE = $(SOURCES:.c=.o)
NAME = libft.a

all: $(NAME)

$(NAME):
	$(COMPILER) $(FLAGS) $(SOURCES) -I $(HEADER)
	ar rc $(LIBNAME) $(OFILE)
	ranlib $(LIBNAME)

clean:
	/bin/rm -f $(OFILE)

fclean: clean
	/bin/rm -f $(LIBNAME)

re: fclean all
