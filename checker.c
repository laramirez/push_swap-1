#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>
//
#include <stdio.h>


void	processops(t_stack **stacka, t_stack **stackb, t_op *oplist)
{
	t_op	*begin;

	begin = oplist;
	if (!(begin->fp))
	{
		ft_printf("you got here\n");
		return ;
	}
	while (begin)
	{
		begin->fp(stacka, stackb);
		begin = begin->next;
		debug_pstacks(*stacka, *stackb);
	}
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
	ft_printf("INPUT VALIDATED, INSERT OP COMMANDS\n");
	oplist = getoplist();

	processops(&stacka, &stackb, oplist);
	//ft_printf("After sorting\n");
	//debug_pstacks(stacka, stackb);


	ft_printf("END OF PROGRAM\n");
	return (0);
}
