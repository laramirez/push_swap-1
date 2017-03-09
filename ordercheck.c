#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>

int		isrevordered(t_stack *stacka, t_stack *stackb)
{
	int tmp;

	if (stacka)
		return (0);
	else if (!(stackb))
		return (0);
	tmp = stackb->v;
	while (stackb->nx)
	{
		if ((stackb->nx)->v < tmp)
			tmp = (stackb->nx)->v;
		else if ((stackb->nx)->v == tmp)
			return (2);
		else
			return (0);
		stackb = stackb->nx;
	}
	return (1);
}

int		revordered(t_stack *stackb)
{
	int tmp;

	if (!(stackb))
		return (0);
	tmp = stackb->v;
	while (stackb->nx)
	{
		if ((stackb->nx)->v <  tmp)
			tmp = (stackb->nx)->v;
		else if ((stackb->nx)->v == tmp)
			return (2);
		else
			return (0);
		stackb = stackb->nx;
	}
	return (1);
}

int		ordered(t_stack *stackb)
{
	int tmp;

	if (!(stackb))
		return (0);
	tmp = stackb->v;
	while (stackb->nx)
	{
		if ((stackb->nx)->v > tmp)
			tmp = (stackb->nx)->v;
		else if ((stackb->nx)->v == tmp)
			return (2);
		else
			return (0);
		stackb = stackb->nx;
	}
	return (1);
}
