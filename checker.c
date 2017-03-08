#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>


void	processops(t_stack **stacka, t_stack **stackb, t_op *oplist)
{
	t_op	*begin;

	begin = oplist;
	if (!(begin->fp))
	{
		return ;
	}
	//
	debug_pstacks(*stacka, *stackb);
	while (begin)
	{
		begin->fp(stacka, stackb);
		begin = begin->next;
		/*
		** INSER DEBUG CODE WITH FLAG HERE.
		*/
		//
		debug_pstacks(*stacka, *stackb);
	}
}

int		isordered(t_stack *stacka, t_stack *stackb)
{
	int tmp;

	if (stackb)
		return (0);
	else if (!(stacka))
		return (0);
	tmp = stacka->v;
	while (stacka->nx)
	{
		if ((stacka->nx)->v > tmp)
			tmp = (stacka->nx)->v;
		else if ((stacka->nx)->v == tmp)
			return (2);
		else
			return (0);
		stacka = stacka->nx;
	}
	return (1);
}

int main(int ac, char **av)
{
	t_op	*oplist;
	t_stack	*stacka;
	t_stack *stackb;
	int		tmp;

	tmp = 0;
	stacka = NULL;
	stackb = NULL;
	if (!(stacka = valinput(ac, av, stacka)))
			return (0);
	oplist = getoplist();
	processops(&stacka, &stackb, oplist);
	if ((tmp = isordered(stacka, stackb)))
	{
		if (tmp == 1)
			ft_printf("OK\n");
		else
			write(2, "Error\n", 6);
	}
	else
		ft_printf("KO\n");
	return (0);
}
