#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>
//
#include <stdio.h>

void	fsa(t_stack **stacka, t_stack **stackb)
{
	t_stack *tmpa;
	t_stack *tmpb;

	tmpb = *stackb;
	if (*stacka && (*stacka)->nx)
	{
		tmpa = (*stacka)->nx;
		(*stacka)->nx = tmpa->nx;
		tmpa->nx = (*stacka);
		*stacka = tmpa;
	}
}

void	processops(t_stack **stacka, t_stack **stackb, t_op *oplist)
{
	t_op	*begin;

	begin = oplist;
	if (!(begin->fp))
		return ;
	while (begin)
	{
		oplist->fp(stacka, stackb);
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

	//debug
	ft_printf("Before Sorting\n");
	debug_pstacks(stacka, stackb);

	//sorting functions
	processops(&stacka, &stackb, oplist);
	ft_printf("After sorting\n");
	debug_pstacks(stacka, stackb);


	ft_printf("END OF PROGRAM\n");
	return (0);
}

/*
$>./checker 3 2 1 0
rra
pb sa
rra pa
OK
*/
