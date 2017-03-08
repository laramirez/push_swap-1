# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgould <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/22 11:22:29 by mgould            #+#    #+#              #
#    Updated: 2017/03/06 14:50:18 by mgould           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = checker

NAME2 = push_swap

LIB = /nfs/2016/m/mgould/thelibrary/

LIBA = /nfs/2016/m/mgould/thelibrary/libft.a

CFLAGS = -Wall -Wextra -Werror -I $(LIB) -I .

OBJCS = checker.o initstruct.o valinput.o debug.o fswap.o fpush.o frot.o \
		frevrot.o valops.o

OBJCS2 = push_swap.o valinput.o initstruct.o fswap.o fpush.o frot.o \
		 frevrot.o valops.o ordercheck.o debug.o

all: $(NAME1) $(NAME2)

$(NAME1): $(OBJCS) $(LIBA)
	gcc $(CFLAGS) -o $@ $^

#make sure to remove this make clean!
$(NAME2): $(OBJCS2) $(LIBA)
	gcc $(CFLAGS) -o $@ $^
	make clean


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
