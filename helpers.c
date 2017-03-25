#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>

int	stacklen(t_stack *stack)
{
	int i;
	t_stack *tmp;

	tmp = stack;
	i = 0;
	while (tmp)
	{
		tmp = tmp->nx;
		i++;
	}
	return (i);
}

t_stack	*getend(t_stack **stack)
{
	t_stack *end;

	if (!(*stack))
		return (NULL);
	end = *stack;
	while (end->nx)
		end = end->nx;
	return (end);
}

int	aassigngroups(t_stack **stack)
{
	int i;
	int tmp;
	t_stack *stemp;

	if (!(*stack))
		return (0);
	stemp = *stack;
	tmp = (stemp)->v;
	i = 1;
	while (stemp)
	{
		if ((stemp)->v >= tmp)
		{
			(stemp)->g = i;
			tmp = stemp->v;
		}
		else
		{
			i++;
			tmp = (stemp)->v;
			continue;
		}
		(stemp) = (stemp)->nx;
	}
	return (i);
}

int	bassigngroups(t_stack **stack)
{
	int i;
	int tmp;
	t_stack *stemp;

	if (!(*stack))
		return (0);
	i = -1;
	stemp = *stack;
	tmp = (stemp)->v;
	while (stemp)
	{
		if ((stemp)->v <= tmp)
		{
			(stemp)->g = i;
			tmp = stemp->v;
		}
		else
		{
			i--;
			tmp = (stemp)->v;
			continue;
		}
		stemp = (stemp)->nx;
	}
	return (i * -1);
}

/*
int getminrun(t_stack *stacka)
{
	int i;
	int ret;

	ret = 0;
	//set the minimum lower boundary here, currently at 16
	i = 16;
	ret = stacklen(stacka);
	if (ret < 65)
	{
		if (ret < i && ret > 1)
			ret = i;
	}
	else
	{
		while ((ret = (ret / i)) > 64)
			i *= 2;
	}
	return (ret);
}
*/
