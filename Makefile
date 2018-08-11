# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/11 11:29:48 by ttshivhu          #+#    #+#              #
#    Updated: 2018/08/11 11:59:06 by ttshivhu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OTOOL = ft_otool
NM = ft_nm
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC = free.c nm.c nm32bit.c common.c common2.c ranlib.c utils.c otool.c \

OBJ = $(SRC:.c=.o)
all: $(OTOOL)

$(OTOOL): $(OBJ)
	@make -C libft
	@gcc -c $(CFLAGS) otoolmain.c
	@gcc -c $(CFLAGS) nmmain.c
	@gcc $(OBJ) otoolmain.o $(CFLAGS) -Llibft -lft -o $(OTOOL)
	@gcc $(OBJ) nmmain.o $(CFLAGS) -Llibft -lft -o $(NM)
	@printf "\x1b[32mCompiled $(OTOOL) and $(NM)\x1b[0m\n"

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJ)
	@/bin/rm -f otoolmain.o nmmain.o

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(OTOOL) $(NM)

re: fclean all
