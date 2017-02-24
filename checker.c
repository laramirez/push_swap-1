#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
//
#include <stdio.h>

int	arenumbers(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

t_op	*opsinit()
{
	t_op *list;

	list = (t_op *)(malloc(sizeof(t_op)));
	list->op = nothing;
	list->next = NULL;
	return (list);
}

int		notgetop(t_op *list, char *line)
{
	if (!(strcmp(line, "sa")))
		list->op = sa;
	else if (!(strcmp(line, "sb")))
		list->op = sb;
	else if (!(strcmp(line, "ss")))
		list->op = ss;
	else if (!(strcmp(line, "pa")))
		list->op = pa;
	else if (!(strcmp(line, "pb")))
		list->op = pb;
	else if (!(strcmp(line, "ra")))
		list->op = ra;
	else if (!(strcmp(line, "rb")))
		list->op = rb;
	else if (!(strcmp(line, "rr")))
		list->op = rr;
	else if (!(strcmp(line, "rra")))
		list->op = rra;
	else if (!(strcmp(line, "rrb")))
		list->op = rrb;
	else if (!(strcmp(line, "rrr")))
		list->op = rrr;
	else
		return (1);
	return (0);
}

int	valinput(int ac, char **av)
{
	int	len;

	len = 0;
	//
	while (av[len])
	{
		ft_putstr(av[len]);
		ft_putchar('\n');
		len++;
	}
	if (ac < 2)
	{
		//display nothing.
		printf("enter in a sequence of nubmers");
		return (0);
	}
	if (!arenumbers(av))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	return (1);
}

t_op *getoplist()
{
	int		i;
	char	*line;
	t_op	*list;
	t_op	*begin;

	i = 0;
	line = NULL;
	list = opsinit();
	begin = list;
	while (get_next_line(0, &line))
	{
		if (i == 0)
		{
			begin = list;
		}
		if (notgetop(list, line))
		{
			ft_printf("KO\n");
			return (0);
		}
		list->next = opsinit();
		list = list->next;
		i++;
	}
	return (begin);
}

int main(int ac, char **av)
{
	t_op	*begin;
	t_stack	*stacka;

	//makes sense to add integer list creation to valinput
	//b/c it is already reading through once.  can try it.
	//can also just make a second function if pointers get ugly :-)
	stacka = NULL;
	//want to say top = valinput, and return NULL;
	if (!(valinput(ac, av)))
			return (0);
	begin = getoplist();

	//now is where you start executing instructions on the stack.
	while (begin)
	{
		if (!(begin->op == nothing))
			printf("op:%d\n", begin->op);
		begin = begin->next;
	}
	ft_putstr("END OF PROGRAM\n");
	return (0);
}
