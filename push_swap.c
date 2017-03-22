#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>
//
#include <stdio.h>

int		getlargest(t_stack *sb)
{
	int		largest;
	t_stack	*tmp;

	tmp = sb;
	largest = tmp->v;
	while (tmp)
	{
		if (largest < tmp->v)
			largest = tmp->v;
		tmp = tmp->nx;
	}
	return (largest);
}


int		getsmallest(t_stack *sb)
{
	int		smallest;
	t_stack	*tmp;

	tmp = sb;
	smallest = tmp->v;
	while (tmp)
	{
		if (smallest > tmp->v)
			smallest = tmp->v;
		tmp = tmp->nx;
	}
	return (smallest);
}

void	updateretstack(t_out *ret, t_onum op, t_stack **sa, t_stack **sb)
{
	t_out *tmp;

	tmp = ret;
	while (tmp->nx)
		tmp = tmp->nx;
	tmp->num = op;
	tmp->nx = outinit();
	doop(op, sa, sb);
}

/* DEBUG PRINTERS

ft_putstr_color_fd("second while of merge function-\n\n", 2, 2);
ft_putstr_color_fd("after moving to insertion spot\n\n", 2, 2);
ft_putstr_color_fd("before moving to insertion spot top\n\n", 2, 2);
ft_putstr_color_fd("rotating back to start\n\n", 1, 2);
ft_putstr_color_fd("before moving to insertion spot\n\n", 2, 2);
ft_putstr_color_fd("after second while of merge function-\n\n", 2, 2);
ft_putstr_color_fd("\n after rotating stack B\n\n", 1, 2);

*/



void	mergestack(t_stack **sa, t_stack **sb, t_out *ret)
{
	t_stack *tmpb;
	int		group;
	t_stack *end;
	int		largest;


	if (!(*sb))
		return ;
	largest = 0;
	group = (*sb)->g;
	tmpb = *sb;
	while ((*sb)->g == group)
	{
		updateretstack(ret, PA, sa, sb);
	}
	while ((*sa)->g == group)
	{
		end = getend(sb);
		if (ordered(*sa))
			break;
		else if ((*sa)->v < end->v && ((*sa)->v) < (*sb)->v)
		{
			updateretstack(ret, PB, sa, sb);
			updateretstack(ret, RB, sa, sb);
		}
		else if ((*sa)->v < (*sb)->v)
		{
			while ((*sa)->v < (*sb)->v)
			{
				updateretstack(ret, RB, sa, sb);
			}
			updateretstack(ret, PB, sa, sb);
		}
		else if ((*sa)->v > (*sb)->v && !((*sa)->v < end->v))
		{
			if ((*sa)->v > (largest = getlargest(*sb)))
			{
				while ((*sb)->v != largest)
				{
					updateretstack(ret, RRB, sa, sb);
				}
			}
			else
			{
				while (((*sa)->v > (*sb)->v) && ((*sa)->v > end->v))
				{
					updateretstack(ret, RRB, sa, sb);
					end = getend(sb);
				}
			}
			updateretstack(ret, PB, sa, sb);
		}
		else
		{
			updateretstack(ret, PB, sa, sb);
		}
	}
	largest = getlargest(*sb);
	while ((*sb)->v != largest)
	{
		updateretstack(ret, RB, sa, sb);
	}
	bassigngroups(sb);
}

void	mergetwo(t_stack **sa, t_stack **sb, t_out *ret)
{
	int	smallest;
	int largest;
	t_stack *end;

	while (*sb)
	{
		end = getend(sa);
		if ((*sb)->v < (smallest = getsmallest(*sa)))
		{
			while ((*sa)->v != smallest)
				updateretstack(ret, RA, sa, sb);
			updateretstack(ret, PA, sa, sb);
		}
		else if ((*sa)->v > (largest = getlargest(*sb)) && ordered(*sa))
		{
			while ((*sb)->v != largest)
				updateretstack(ret, RB, sa, sb);
			updateretstack(ret, PA, sa, sb);
		}
		else if ((*sb)->v > (*sa)->v)
			updateretstack(ret, RA, sa, sb);
		else if ((*sb)->v < (*sa)->v && (*sb)->v > end->v)
			updateretstack(ret, PA, sa, sb);
		else if ((*sb)->v < (*sa)->v && (*sb)->v < end->v)
			updateretstack(ret, RRA, sa, sb);
	}
	smallest = getsmallest(*sa);
	while ((*sa)->v != smallest)
		updateretstack(ret, RA, sa, sb);
}

void	printret(t_out *ret)
{
	int i;

	i = 0;
	while (ret)
	{
		if (ret->num == NOTHING)
			break;
		printelement2(ret->num);
		ret = ret->nx;
		i++;
	}
}

void	timdecision(t_stack **sa, t_stack **sb, t_stack *end, t_out *ret)
{
	if ((!(*sa)->nx) || ((*sa)->v < end->v && (*sa)->v < ((*sa)->nx)->v))
	{
		if ((*sb) && ((*sa)->v < (*sb)->v) && (bassigngroups(sb) > 1))
			mergestack(sa, sb, ret);
		updateretstack(ret, PB, sa, sb);
	}
	else if (((*sa)->nx)->v < (*sa)->v)
	{
		updateretstack(ret, SA, sa, sb);
	}
	else if (((*sa)->nx)->v <= (end)->v && ((*sa)->nx)->v < (*sa)->v)
	{
		updateretstack(ret, SA, sa, sb);
	}
	else if ((((stacklen(*sa) == 1) && (end->v < (*sa)->v))) ||
			(end->v < (*sa)->v && (end)->v <= ((*sa)->nx)->v))
	{
		updateretstack(ret, RRA, sa, sb);
	}
	if((*sb) && (*sb)->v < ((getend(sb))->v))
	{
		updateretstack(ret, RB, sa, sb);
	}
}

int	retnumber(t_out *ret)
{
	int i;

	i = 0;
	while (ret->num != NOTHING)
	{
		i++;
		ret = ret->nx;
	}
	return (i);
}

void	stim(t_stack **sa, t_stack **sb, t_out *ret)
{
	int i;
	t_stack *end;

	i = 0;
	end = getend(sa);
	if (aassigngroups(sa) == 1)
		return ;
	while (*sa)
	{
		timdecision(sa, sb, end, ret);
		aassigngroups(sa);
		bassigngroups(sb);
		end = getend(sa);
		if (ordered(*sa))
		{
			while (bassigngroups(sb) > 1)
				mergestack(sa, sb, ret);
			mergetwo(sa, sb, ret);
			break;
		}
	}
}

int main(int ac, char **av)
{
	t_stack	*stacka;
	t_stack *stackb;
	t_out	*ret;

	stacka = NULL;
	stackb = NULL;
	ret = outinit();
	if (!(stacka = valinput(ac, av, stacka)))
			return (0);
	//SORTING ALGO
	stim(&stacka, &stackb, ret);

	//PRINT OPS AND OPS NUMBER OF OPS
	fprintf(stderr, "ret number is %d\n", retnumber(ret));
	printret(ret);
	return (0);
}


















