#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>


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

void	fsb(t_stack **stacka, t_stack **stackb)
{
	t_stack *tmpa;
	t_stack *tmpb;

	tmpa = *stacka;
	if (*stackb && (*stackb)->nx)
	{

		tmpb = (*stackb)->nx;
		(*stackb)->nx = tmpb->nx;
		tmpb->nx = (*stackb);
		*stackb = tmpb;
	}
}
