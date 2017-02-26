#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>
//
#include <stdio.h>


void	process_op(t_stack *stacka, t_stack *stackb, t_op *list)
{
	stacka = NULL;
	stackb = NULL;
	list = NULL;
}

void	process_ops(t_stack *stacka, t_stack *stackb, t_op *list)
{
	t_op	*begin;

	begin = list;
	while (begin)
	{
		process_op(stacka, stackb, list);
	}
}

int main(int ac, char **av)
{
	t_op	*begin;
	t_stack	*stacka;
	t_stack *stackb;

	stacka = NULL;
	stackb = NULL;
	if (!(stacka = valinput(ac, av, stacka)))
			return (0);
	ft_printf("INPUT VALIDATED, INSERT OP COMMANDS\n");
	begin = getoplist();

	//interactive debug
	printf("Before Sorting\n");
	debug_pstacks(stacka, stackb);

	//sorting functions

	printf("after sorting\n");
	//debug_pstacks(stacka, stackb);


	ft_putstr("END OF PROGRAM\n");
	return (0);
}

/*
$>./checker 3 2 1 0
rra
pb sa
rra pa
OK
*/
