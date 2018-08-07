# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/07 08:39:04 by ttshivhu          #+#    #+#              #
#    Updated: 2017/08/13 11:48:35 by ttshivhu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = convert.c ft_printf.c helpers.c master.c mem.c octal.c string.c hex.c color.c \
unsigned_d.c wstring.c binary.c cleaners.c ft_putfloat.c \

FLAG = -Wall -Werror -Wextra

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@make -C libft
	@gcc $(FLAG) -c $(SRC)
	@ar rc $(NAME) $(OBJ) libft/*.o
	@ranlib $(NAME)

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJ) $(LOBJ) *.o

fclean: clean
		@/bin/rm -f $(NAME)
		@make fclean -C libft

re: fclean all
