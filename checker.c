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
	while (begin)
	{
		begin->fp(stacka, stackb);
		begin = begin->next;
		debug_pstacks(*stacka, *stackb);
	}
}

int		isordered(t_stack *stacka, t_stack *stackb)
{
	int tmp;

	if (stackb)
	{
		return (0);
	}
	else if (!(stacka))
		return (0);
	tmp = stacka->v;
	while (stacka->nx)
	{
		if ((stacka->nx)->v > tmp)
			tmp = stacka->v;
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

	stacka = NULL;
	stackb = NULL;
	if (!(stacka = valinput(ac, av, stacka)))
			return (0);
	//ft_printf("INPUT VALIDATED, INSERT OP COMMANDS\n");
	oplist = getoplist();
	processops(&stacka, &stackb, oplist);
	if (isordered(stacka, stackb))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	//ft_printf("END OF PROGRAM\n");
	return (0);
}
