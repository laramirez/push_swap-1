# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgould <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/22 11:22:29 by mgould            #+#    #+#              #
#    Updated: 2017/03/04 19:02:07 by mgould           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = a.out

NAME2 = push_swap

LIB = /nfs/2016/m/mgould/thelibrary/

LIBA = /nfs/2016/m/mgould/thelibrary/libft.a

CFLAGS = -Wall -Wextra -Werror -I $(LIB) -I .

OBJCS = checker.o initstruct.o valinput.o debug.o fswap.o fpush.o

all: $(NAME1)

$(NAME1): $(OBJCS) $(LIBA)
	gcc $(CFLAGS) -o $@ $^
	make clean

$(LIBA):
	cd $(LIB) && $(MAKE)

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJCS)

#cd $(LIB) && make fclean, will add later, not necessary for debug

fclean: clean
	rm -f $(NAME1)

re: fclean all

.PHONY: clean re fclean

