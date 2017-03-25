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
	if((*sb) && (*sb)->v < ((getend(sb))->v))
		updateretstack(ret, RB, sa, sb);
	else if((*sb) && (*sb)->nx && (*sb)->v < ((*sb)->nx)->v)
		updateretstack(ret, SB, sa, sb);

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

	return (0);
}

void	astructmoves(t_stack *sa)
{
	int i;
	t_stack *tmpa2;

	i = 0;
	tmpa2 = sa;
	while (sa)
	{
		sa->maf = i;
		sa = sa->nx;
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

void	bstructmoves(t_stack *sa, t_stack *sb)
{
	int i;
	t_stack *tmpb;

	while (sa)
	{
		i = 0;
		tmpb = sb;
		if (sa->v > getlargest(sb))
		{
			sa->mbf = 0;
			sa->mbr = 0;
		}
		else if (sa->v < getsmallest(sb))
		{
			sa->mbf = 0;
			sa->mbr = 0;
		}
		else
		{
			while (sa->v < tmpb->v)
			{
				i++;
				tmpb = tmpb->nx;
			}
			sa->mbf = i;
			sa->mbr = stacklen(sb) - i;
		}
		sa = sa->nx;
	}
}

void	movedir(t_stack *sa)
{
	int forward;
	int reverse;

	while (sa)
	{
		forward = ((sa->maf > sa->mbf) ? sa->maf : sa->mbf);
		reverse = ((sa->mar > sa->mbr) ? sa->mar : sa->mbr);
		sa->moves = ((forward < reverse) ? forward : reverse);
		if (forward <= reverse)
			sa->dir = 1;
		else
			sa->dir = -1;
		sa = sa->nx;
	}
}

	//find the lowest value in stack A
	//execute it's moves in the proper direction for each stack
	//check if sorted along the way if possible

void	insertbest(t_stack **sa, t_stack **sb, t_out *ret)
{
	t_stack *tmp;
	int	moves;
	int dir;
	int b;
	int a;

	moves = 0;
	tmp = *sa;
	while (tmp)
	{
		if (tmp->moves < moves)
		{
			moves = tmp->moves;
			dir = tmp->dir;
			b = (dir < 0 ? tmp->mbr : tmp->mbf);
			a = (dir < 0 ? tmp->mar : tmp->maf);
			moves = tmp->moves;
		}

		tmp = tmp->nx;
	}
	//function here to rotate the stack pre-pop
	while (moves)
	{
		if (dir < 0)
		{
			if (b > 0 & a > 0)
				updateretstack(ret, RRR, sa, sb);
			else if (b > 0)
				updateretstack(ret, RRB, sa, sb);
			else if (a > 0)
				updateretstack(ret, RRA, sa, sb);
		}
		else if (dir > 0)
		{
			if (b > 0 & a > 0)
				updateretstack(ret, RR, sa, sb);
			else if (b > 0)
				updateretstack(ret, RB, sa, sb);
			else if (a > 0)
				updateretstack(ret, RA, sa, sb);
		}
		if (ordered(*sa))
			return ;
		a--;
		b--;
		moves--;
	}
	updateretstack(ret, PB, sa, sb);
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
			astructmoves(*sa);
			bstructmoves(*sa, *sb);
			movedir(*sa);
			//
			//debug_pstacks(*sa, *sb);
			insertbest(sa, sb, ret);
			//debug_pstacks(*sa, *sb);

		}
		end = getend(sa);
		if (ordered(*sa))
		{
			mergetwo(sa, sb, ret);
			break;
		}
	}
}














