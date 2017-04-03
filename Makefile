# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgould <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/22 11:22:29 by mgould            #+#    #+#              #
#    Updated: 2017/03/23 21:31:34 by mgould           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = checker

NAME2 = push_swap

LIB = libft

LIBA = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -I $(LIB) -I .

OBJCS = debug.o checker.o initstruct.o valinput.o debug.o fswap.o fpush.o \
		frot.o frevrot.o valops.o helpers.o

OBJCS2 = debug.o push_swap.o valinput.o initstruct.o fswap.o fpush.o frot.o \
		 frevrot.o valops.o ordercheck.o helpers.o initstructhelp.o \
		 rethelp.o fortysort.o bstructmoves.o movedir.o \
		 prepoprot.o rethelp2.o

all: $(NAME1) $(NAME2)

$(NAME1): $(OBJCS) $(LIBA)
	gcc $(CFLAGS) -o $@ $^

$(NAME2): $(OBJCS2) $(LIBA)
	gcc $(CFLAGS) -o $@ $^

$(LIBA):
	cd $(LIB) && $(MAKE)

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJCS)
	rm -f $(OBJCS2)
	cd $(LIB) && make fclean

fclean: clean
	rm -f $(NAME1)
	rm -f $(NAME2)

re: fclean all

.PHONY: clean re fclean
