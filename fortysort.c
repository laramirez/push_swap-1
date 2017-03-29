#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>
//
#include <stdio.h>


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
		if (wheredest(*sa) >= 0)
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
		//
		fprintf(stderr, "you are at merge two loop\n");
		debug_pstacks(*sa, *sb);
		end = getend(sa);
		if ((*sb)->v < (smallest = getsmallest(*sa)))
		{
			fprintf(stderr, "one\n");
			while ((*sa)->v != smallest)
				updateretstack(ret, RA, sa, sb);
			updateretstack(ret, PA, sa, sb);
		}
		else if ((*sb)->v > (largest = getlargest(*sa)) && ordered(*sa))
		{
			fprintf(stderr, "two\n");
			largest = getlargest(*sb);
			while ((*sb)->v != largest)
				updateretstack(ret, RB, sa, sb);
			updateretstack(ret, PA, sa, sb);
		}
		else if ((*sb)->v > (*sa)->v)
		{
			updateretstack(ret, RA, sa, sb);
			fprintf(stderr, "thr:\n");
		}
		else if ((*sb)->v < (*sa)->v && (*sb)->v > end->v)
		{
			fprintf(stderr, "four\n");
			updateretstack(ret, PA, sa, sb);
		}
		else if ((*sb)->v < (*sa)->v && (*sb)->v < end->v)
		{
			fprintf(stderr, "five\n");
			updateretstack(ret, RRA, sa, sb);
		}
	}
	smallest = getsmallest(*sa);
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
	t_stack *prev;

	tmpb = sb;
	prev = tmpb;
	if (!(sb))
		return ;
	while (sa)
	{
		i = 0;
		tmpb = sb;
		if (sa->v > getlargest(sb))
		{
			while (tmpb->v != getlargest(sb))
			{
				i++;
				tmpb = tmpb->nx;
			}
			sa->mbf = i;
			sa->mbr = (stacklen(sb) - i);
		}
		else if (sa->v < getsmallest(sb))
		{
			i++;
			while (tmpb->v != getsmallest(sb))
			{
				i++;
				tmpb = tmpb->nx;
			}
			sa->mbf = i;
			sa->mbr = (stacklen(sb) - i);
		}
		else
		{
			if (sa->v < (getend(&tmpb)->v) && sa->v > tmpb->v)
			{
				;
			}
			else if (sa->v > (getend(&tmpb)->v) && sa->v > tmpb->v)
			{
				i++;
				while (sa->v > tmpb->v)
				{
					i++;
					tmpb = tmpb->nx;
				}
			}
			else if (sa->v < (getend(&tmpb)->v) && sa->v < tmpb->v)
			{
				while (sa->v < tmpb->v)
				{
					i++;
					tmpb = tmpb->nx;
				}
			}
			else
			{
				i++;
				while (sa->v < tmpb->v )
				{
					i++;
					tmpb = tmpb->nx;
				}
			}
			sa->mbf = i;
			sa->mbr = (stacklen(sb) + 1) - i;
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



void	insertbest(t_stack **sa, t_stack **sb, t_out *ret)
{
	t_stack *tmp;
	int	moves;
	int dir;
	int b;
	int a;

	tmp = *sa;
	moves = tmp->moves;
	dir = tmp->dir;
	b = (dir < 0 ? tmp->mbr : tmp->mbf);
	a = (dir < 0 ? tmp->mar : tmp->maf);
	while (tmp)
	{
		if (tmp->moves < moves)
		{
			moves = tmp->moves;
			dir = tmp->dir;
			b = (dir < 0 ? tmp->mbr : tmp->mbf);
			a = (dir < 0 ? tmp->mar : tmp->maf);
		}

		tmp = tmp->nx;
	}
	//function here to rotate the stack pre-pop
	fprintf(stderr, "dir:%d, b:%d, a:%d, moves:%d\n", dir, b, a, moves);
	while (moves)
	{
		debug_pstacks(*sa, *sb);
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
		astructmoves(*sa);
		bstructmoves(*sa, *sb);
		movedir(*sa);

		fprintf(stderr, "before insert best decision\n");
		debug_pstacks(*sa, *sb);

		insertbest(sa, sb, ret);

		fprintf(stderr, "after insert best decision\n");
		debug_pstacks(*sa, *sb);

		end = getend(sa);
		if (almostordered(*sa))
		{
			fprintf(stderr, "almost ordered looks like:\n\n");
			debug_pstacks(*sa, *sb);
			fprintf(stderr, "\n\n");
			mergetwo(sa, sb, ret);
			fprintf(stderr, "after merge loop looks like:\n\n");
			debug_pstacks(*sa, *sb);
			rotcor(ret, sa, sb, 0);
			break;
		}
	}
	fprintf(stderr, "AT THE END\n");
	debug_pstacks(*sa, *sb);

}













	//find the lowest value in stack A
	//execute it's moves in the proper direction for each stack
	//check if sorted along the way if possible

/*
*/

/*
static int	fortydecision(t_stack **sa, t_stack **sb, t_stack *end, t_out *ret)
{
	debug_pstacks(*sa, *sb);
	if((*sb) && (*sb)->v < ((getend(sb))->v))
		updateretstack(ret, RB, sa, sb);
	else if((*sb) && (*sb)->nx && (*sb)->v < ((*sb)->nx)->v)
		updateretstack(ret, SB, sa, sb);

	if ((!(*sa)->nx) || ((*sa)->v < end->v && (*sa)->v < ((*sa)->nx)->v))
	{
		return (1);

		if ((*sb) && ((*sa)->v < (*sb)->v))
		{
			return (1);
		}
		fprintf(stderr, "push b from fortydecision\n");
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
*/
