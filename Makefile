# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/11 11:29:48 by ttshivhu          #+#    #+#              #
#    Updated: 2018/08/11 11:54:18 by ttshivhu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OTOOL = ft_otool
NM = ft_nm
AS = gcc
FLAGS = -Wall -Werror -Wextra
SRC = free.c nm.c nm32bit.c common.c common2.c ranlib.c utils.c otool.c \

OBJ = $(SRC:.c=.o)
all: $(OTOOL)

$(OTOOL): $(OBJ)
	@make -C libft
	@gcc -c $(FLAGS) otoolmain.c
	@gcc -c $(FLAGS) nmmain.c
	@gcc $(OBJ) otoolmain.o $(FLAGS) -Llibft -lft -o $(OTOOL)
	@gcc $(OBJ) nmmain.o $(FLAGS) -Llibft -lft -o $(NM)
	@printf "Compiled $(OTOOL) and $(NM)\n"

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJ)
	@/bin/rm -f otoolmain.o nmmain.o

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(OTOOL) $(NM)

re: fclean all
