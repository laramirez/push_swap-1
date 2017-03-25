#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>

static void	rotcor(t_out *ret, t_stack **sa, t_stack **sb, int descending)
{
	int tmp;

	tmp = 0;
	if (descending)
	{
		tmp = getlargest(*sb);
		if (wheredest(*sb))
			while ((*sb)->v != tmp)
				updateretstack(ret, RB, sa, sb);
		else
			while ((*sb)->v != tmp)
				updateretstack(ret, RRB, sa, sb);
		bassigngroups(sb);
	}
	else
	{
		tmp = getsmallest(*sa);
		if (wheredest(*sa))
			while ((*sa)->v != tmp)
				updateretstack(ret, RA, sa, sb);
		else
			while ((*sa)->v != tmp)
				updateretstack(ret, RRA, sa, sb);
		aassigngroups(sa);
	}
}

static void	mergetwo(t_stack **sa, t_stack **sb, t_out *ret)
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
	rotcor(ret, sa, sb, 0);
}

static int	fortydecision(t_stack **sa, t_stack **sb, t_stack *end, t_out *ret)
{
	if ((!(*sa)->nx) || ((*sa)->v < end->v && (*sa)->v < ((*sa)->nx)->v))
	{
		if ((*sb) && ((*sa)->v < (*sb)->v))
		{
			return (1);
		}
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
	return (0);
}

/*

void	movecalc(t_stack *stack, t_stack *sb, int num)
{
	int i;

	i = 0;
	while (stack->v != num)
	{
		i++;
		stack = stack->nx;
	}

}

*/

	//track which direction that move is
	//take the min of the two directional values, this is 'moves'
	//min of the two directional values, determines direction of the max 'dir'
	//find the lowest value in stack A
	//execute it's moves in the proper direction for each stack
	//pop off along the way if possible
	//check if sorted along the way if possible

void	astructmovesf(t_stack *sa)
{
	int i;
	t_stack *tmpa;
	t_stack *tmpa2;

	i = 0;
	tmpa = sa;
	tmpa2 = sa;
	while (tmpa)
	{
		tmpa->maf = i;
		tmpa = tmpa->nx;
		i++;
	}
	tmpa2->mar = 0;
	tmpa2 = tmpa2->nx;
	i--;
	while (tmpa2)
	{
		tmpa2->mar = i;
		tmpa2 = tmpa2->nx;
		i--;
	}
}


void	fortysort(t_stack **sa, t_stack **sb, t_out *ret)
{
	int i;
	t_stack *end;

	i = 0;
	end = getend(sa);
	if (aassigngroups(sa) == 1)
		return ;
	while (*sa)
	{
		if (fortydecision(sa, sb, end, ret))
		{
			astructmovesf(*sa);
			//calcualte b moves for each a
			debug_pstacks(*sa, *sb);
			//this is where you do the moves stuff
			return ;

		}
		aassigngroups(sa);
		bassigngroups(sb);
		end = getend(sa);
		if (ordered(*sa))
		{
			mergetwo(sa, sb, ret);
			break;
		}
	}
}














