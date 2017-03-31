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

LIB = /nfs/2016/m/mgould/thelibrary/

LIBA = /nfs/2016/m/mgould/thelibrary/libft.a

CFLAGS = -Wall -Wextra -Werror -I $(LIB) -I .

OBJCS = debug.o checker.o initstruct.o valinput.o debug.o fswap.o fpush.o \
		frot.o frevrot.o valops.o helpers.o

OBJCS2 = debug.o push_swap.o valinput.o initstruct.o fswap.o fpush.o frot.o \
		 frevrot.o valops.o ordercheck.o helpers.o initstructhelp.o \
		 rethelp.o timsort.o fortysort.o bstructmoves.o movedir.o \
		 prepoprot.o

all: $(NAME1) $(NAME2)

$(NAME1): $(OBJCS) $(LIBA)
	gcc $(CFLAGS) -o $@ $^

#make sure to remove this make clean!
#make clean
$(NAME2): $(OBJCS2) $(LIBA)
	gcc $(CFLAGS) -o $@ $^


$(LIBA):
	cd $(LIB) && $(MAKE)

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJCS)
	rm -f $(OBJCS2)

#cd $(LIB) && make fclean, will add later, not necessary for debug

fclean: clean
	rm -f $(NAME1)
	rm -f $(NAME2)

re: fclean all

.PHONY: clean re fclean
