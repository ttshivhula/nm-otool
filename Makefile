# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/11 11:29:48 by ttshivhu          #+#    #+#              #
#    Updated: 2018/08/11 11:36:02 by ttshivhu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OTOOL = ft_otool
NM = ft_nm
AS = gcc
ASFLAGS = -Wall -Werror -Wextra
SRC = free.c nm.c nm32bit.c common.c common2.c ranlib.c utils.c otool.c \
OMAIN = otoolmain.c
NMAIN = nmmain.c

OBJ = $(SRC:.s=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AS) $(OBJ) $(OMAIN) $(ASFLAGS) -o $(OTOOL)
	$(AS) $(OBJ) $(NMAIN) $(ASFLAGS) -o $(NM)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(OTOOL) $(NM)

re: fclean all
