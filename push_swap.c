#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>
//
#include <stdio.h>

//it's easiest to do if there's only 1 list that is ordered on stackb, so let's try
//that way first.

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

void	updateret(t_out *ret, t_onum op)
{
	t_out *tmp;

	tmp = ret;
	while (tmp->nx)
		tmp = tmp->nx;
	tmp->num = op;
	tmp->nx = outinit();

}


void	mergestack(t_stack **sa, t_stack **sb, int *count, t_out *ret)
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
	end = getend(sb);
	while ((*sb)->g == group)
	{
		fpa(sa, sb);
		updateret(ret, PA);
		*count += 1;
	}
	//debug_pstacks(*sa, *sb);
	ft_putstr_color_fd("second while of merge function-\n\n", 2, 2);
	while ((*sa)->g == group)
	{
		if (ordered(*sa))
			break;
		else if ((*sa)->v < end->v && ((*sa)->v) < (*sb)->v)
		{
			//smallest number on stack check
			fpb(sa, sb);
			frb(sa, sb);
			updateret(ret, PB);
			updateret(ret, RB);
			*count += 2;
			continue;
		}
		else if ((*sa)->v < (*sb)->v)
		{
			while ((*sa)->v < (*sb)->v)
			{
				frb(sa, sb);
				updateret(ret, RB);
				*count += 1;
			}
			//debug_pstacks(*sa, *sb);
			ft_putstr_color_fd("after moving to insertion spot\n\n", 2, 2);
			fpb(sa, sb);
			updateret(ret, PB);
		}
		else if ((*sa)->v > (*sb)->v && !((*sa)->v < end->v))
		{
			ft_putstr_color_fd("before moving to insertion spot top\n\n", 2, 2);
			//debug_pstacks(*sa, *sb);
			//if it's greater than everythign else
			if ((*sa)->v > (largest = getlargest(*sb)))
			{
				ft_putstr_color_fd("before moving to insertion spot\n\n", 2, 2);
				while ((*sb)->v != largest)
				{
					frrb(sa, sb);
					updateret(ret, RRB);
					*count += 1;
				}
			}
			else
			{
				ft_putstr_color_fd("rotating back to start\n\n", 1, 2);
				while (((*sa)->v > (*sb)->v) && ((*sa)->v > end->v))
				{
					frrb(sa, sb);
					updateret(ret, RRB);
					*count += 1;
					end = getend(sb);
				}
			}
			//debug_pstacks(*sa, *sb);
			fpb(sa, sb);
			updateret(ret, PB);
		}
		else
		{
			fpb(sa, sb);
			updateret(ret, PB);
		}
		*count += 1;
		end = getend(sb);
	}
	ft_putstr_color_fd("after second while of merge function-\n\n", 2, 2);
	//debug_pstacks(*sa, *sb);
	largest = getlargest(*sb);
	while ((*sb)->v != largest)
	{
		frb(sa, sb);
		updateret(ret, RB);
		*count += 1;
	}
	ft_putstr_color_fd("\n after rotating stack B\n\n", 1, 2);
	bassigngroups(sb);
	//debug_pstacks(*sa, *sb);
}

/*
void	mergestack2(t_stack **sa, t_stack **sb, int *count, t_out ret)
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
	end = getend(sb);
	while ((*sb)->g == group)
	{
		fpa(sa, sb);
		*count += 1;
	}
	debug_pstacks(*sa, *sb);
	ft_putstr_color_fd("second while of merge function-\n\n", 2, 2);
	while ((*sa)->g == group)
	{
		if (ordered(*sa))
			break;
		else if ((*sa)->v < end->v && ((*sa)->v) < (*sb)->v)
		{
			//smallest number on stack check
			fpb(sa, sb);
			frb(sa, sb);
			*count += 2;
			continue;
		}
		else if ((*sa)->v < (*sb)->v)
		{
			while ((*sa)->v < (*sb)->v)
			{
				frb(sa, sb);
				*count += 1;
			}
			debug_pstacks(*sa, *sb);
			ft_putstr_color_fd("after moving to insertion spot\n\n", 2, 2);
			fpb(sa, sb);
		}
		else if ((*sa)->v > (*sb)->v && !((*sa)->v < end->v))
		{
			ft_putstr_color_fd("before moving to insertion spot top\n\n", 2, 2);
			debug_pstacks(*sa, *sb);
			//if it's greater than everythign else
			if ((*sa)->v > (largest = getlargest(*sb)))
			{
				ft_putstr_color_fd("before moving to insertion spot\n\n", 2, 2);
				while ((*sb)->v != largest)
				{
					frrb(sa, sb);
					*count += 1;
				}
			}
			else
			{
				ft_putstr_color_fd("rotating back to start\n\n", 1, 2);
				printf("count is %d\n", *count);
				while (((*sa)->v > (*sb)->v) && ((*sa)->v > end->v))
				{
					frrb(sa, sb);
					*count += 1;
					end = getend(sb);
				}
				printf("count is %d\n", *count);
			}
			debug_pstacks(*sa, *sb);
			fpb(sa, sb);
		}
		else
			fpb(sa, sb);
		*count += 1;
		end = getend(sb);
	}
	ft_putstr_color_fd("after second while of merge function-\n\n", 2, 2);
	debug_pstacks(*sa, *sb);
	largest = getlargest(*sb);
	while ((*sb)->v != largest)
	{
		frb(sa, sb);
		*count += 1;
	}
	ft_putstr_color_fd(ft_itoa(largest), 1, 2);
	ft_putstr_color_fd("\n after rotating stack B\n\n", 1, 2);
	bassigngroups(sb);
	debug_pstacks(*sa, *sb);
}
*/

void	mergetwo(t_stack **sa, t_stack **sb, int *count, t_out *ret)
{
	int	smallest;
	int largest;
	t_stack *end;

	end = getend(sa);
	smallest = getsmallest(*sa);
	largest = getlargest(*sb);
	while (*sb)
	{
		//rotate to smallest
		//rotate to largest (at top of all if else
		if ((*sb)->v < (smallest = getsmallest(*sa)))
		{
			while ((*sa)->v != smallest)
			{
				fra(sa, sb);
				updateret(ret, RA);
				*count += 1;
			}
			fpa(sa, sb);
			updateret(ret, PA);
		}
		else if ((*sa)->v > (largest = getlargest(*sb)) && ordered(*sa))
		{
			while ((*sb)->v != largest)
			{
				frb(sa, sb);
				updateret(ret, RB);
				*count += 1;
			}
			fpa(sa, sb);
			updateret(ret, PA);
		}
		else if ((*sb)->v > (*sa)->v)
		{
			fra(sa, sb);
			updateret(ret, RA);
		}
		else if ((*sb)->v < (*sa)->v && (*sb)->v > end->v)
		{
			fpa(sa, sb);
			updateret(ret, PA);
		}
		else if ((*sb)->v < (*sa)->v && (*sb)->v < end->v)
		{
			frra(sa, sb);
			updateret(ret, RRA);
		}
		*count += 1;
		end = getend(sa);
		//debug_pstacks(*sa, *sb);
	}
	smallest = getsmallest(*sa);
	while ((*sa)->v != smallest)
	{
		fra(sa, sb);
		updateret(ret, RA);
		*count += 1;
	}

}

/*
void	decision(t_stack **sa, t_stack **sb, t_stack *end, int *count)
{
	if ((!(*sa)->nx) || ((*sa)->v < end->v && (*sa)->v < ((*sa)->nx)->v))
	{
		//if only 1 in list, or it is smaller than the other two
		fprintf(stderr, "you are in comp for group 2\n");
		//if ((*sb) && ((*sa)->v < (*sb)->v) && (bassigngroups(sb) > 1))
		if ((*sb) && ((*sa)->v < (*sb)->v) && (bassigngroups(sb) > 1))
		{

			ft_putstr_color_fd("more than one group in stack b\n\n", 2, 2);
			mergestack(sa, sb, count);
			//check the merge size, will have to
			//pass variable to this function.  this is the Tim Sort part
		}
		fprintf(stderr, "two:fpb\n");
		fpb(sa, sb);
	}
	else if (((*sa)->nx)->v < (*sa)->v)
	{
		//do the swap first, since it may solve the puzzle in rotationally ordered
		fsa(sa, sb);
		fprintf(stderr, "two and a half:fsa\n");
	}
	else if (((*sa)->nx)->v <= (end)->v && ((*sa)->nx)->v < (*sa)->v)
	{
		//if nx is less than the other two
		fprintf(stderr, "three:fsa\n");
		fsa(sa, sb);
	}
	else if ((((stacklen(*sa) == 1) && (end->v < (*sa)->v))) ||
			(end->v < (*sa)->v && (end)->v <= ((*sa)->nx)->v))
	{
		// if end is less than the other two
		fprintf(stderr, "four:frra\n");
		frra(sa, sb);
	}
	//this is an optimization
	if((*sb) && (*sb)->v < ((getend(sb))->v))
	{
		frb(sa, sb);
		*count += 1;
	}
	*count += 1;
}
*/


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

void	decision2(t_stack **sa, t_stack **sb, t_stack *end, int *count, t_out *ret)
{
	if ((!(*sa)->nx) || ((*sa)->v < end->v && (*sa)->v < ((*sa)->nx)->v))
	{
		if ((*sb) && ((*sa)->v < (*sb)->v) && (bassigngroups(sb) > 1))
			mergestack(sa, sb, count, ret);
		fpb(sa, sb);
		updateret(ret, PB);
	}
	else if (((*sa)->nx)->v < (*sa)->v)
	{
		fsa(sa, sb);
		updateret(ret, SA);
	}
	else if (((*sa)->nx)->v <= (end)->v && ((*sa)->nx)->v < (*sa)->v)
	{
		fsa(sa, sb);
		updateret(ret, SA);
	}
	else if ((((stacklen(*sa) == 1) && (end->v < (*sa)->v))) ||
			(end->v < (*sa)->v && (end)->v <= ((*sa)->nx)->v))
	{
		frra(sa, sb);
		updateret(ret, RRA);
	}
	if((*sb) && (*sb)->v < ((getend(sb))->v))
	{
		frb(sa, sb);
		updateret(ret, RB);
		*count += 1;
	}
	*count += 1;
}

void	sortstacks(t_stack **sa, t_stack **sb)
{
	t_stack *end;
	int 	count;
	t_out	*ret;

	count = 0;
	end = getend(sa);
	ret = outinit();
	while (*sa)
	{
		//usleep(150000);

		decision2(sa, sb, end, &count, ret);
		//decision(sa, sb, end, &count);
		aassigngroups(sa);
		bassigngroups(sb);
		//debug_pstacks(*sa, *sb);
		end = getend(sa);
		if (ordered(*sa))
		{
			while (bassigngroups(sb) > 1)
			{
				mergestack(sa, sb, &count, ret);
			}
			mergetwo(sa, sb, &count, ret);
			//
			//debug_pstacks(*sa, *sb);
			break;
		}
	}
	//print ops here
	fprintf(stderr, "ops count is %d\n", count);
	printret(ret);
}

void	stim(t_stack **stacka, t_stack **stackb, int minrun)
{
	int i;

	i = 0;
	if (aassigngroups(stacka) == 1)
	{
		fprintf(stderr, "already ordered\n");
		return ;
	}
	fprintf(stderr, "minrun is:%d\n", minrun);
	//debug_pstacks(*stacka, *stackb);
	sortstacks(stacka, stackb);
}

int main(int ac, char **av)
{
	t_stack	*stacka;
	t_stack *stackb;
	int		minrun;

	stacka = NULL;
	stackb = NULL;
	if (!(stacka = valinput(ac, av, stacka)))
			return (0);
	//not currently used, can not use until after group sorting is solved
	minrun = getminrun(stacka);
	//
	stim(&stacka, &stackb, minrun);
	return (0);
}


















