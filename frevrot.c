#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>

void	frra(t_stack **stacka, t_stack **stackb)
{
	t_stack *tmpb;
	t_stack *tmpa;

	tmpb = *stackb;
	tmpa = *stacka;
	if (*stacka && (*stacka)->nx)
	{
		while (tmpa->nx)
			tmpa = tmpa->nx;
		(tmpa->pv)->nx = NULL;
		(*stacka)->pv = tmpa;
		tmpa->nx = *stacka;
		//
		tmpa->pv = NULL;
		*stacka = tmpa;
	}
}

void	frrb(t_stack **stacka, t_stack **stackb)
{
	t_stack *tmpb;
	t_stack *tmpa;

	tmpb = *stackb;
	tmpa = *stacka;
	if (*stackb && (*stackb)->nx)
	{
		while (tmpb->nx)
			tmpb = tmpb->nx;
		(tmpb->pv)->nx = NULL;
		(*stackb)->pv = tmpb;
		tmpb->nx = *stackb;
		*stackb = tmpb;
	}
}

void	frrr(t_stack **stacka, t_stack **stackb)
{
	frra(stacka, stackb);
	frrb(stacka, stackb);
}
