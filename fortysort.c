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
				while (sa->v < tmpb->v)
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


//replace this function with a simple merge function

void	bstructmovesrev(t_stack *sa, t_stack *sb)
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
		if (sa->v < getsmallest(sb))
		{
			while (tmpb->v != getsmallest(sb))
			{
				i++;
				tmpb = tmpb->nx;
			}
			sa->mbf = i;
			sa->mbr = (stacklen(sb) - i);
		}
		else if (sa->v > getlargest(sb))
		{
			i++;
			while (tmpb->v != getlargest(sb))
			{
				i++;
				tmpb = tmpb->nx;
			}
			sa->mbf = i;
			sa->mbr = (stacklen(sb) - i);
		}
		else
		{
			if (sa->v > (getend(&tmpb)->v) && sa->v < tmpb->v)
			{
				//fprintf(stderr, "in the null condition\n");
			}
			else if (sa->v > (getend(&tmpb)->v) && sa->v > tmpb->v)
			{
				//i--;
				while (sa->v > tmpb->v)
				{
					i++;
					tmpb = tmpb->nx;
				}
				/*
				while (sa->v < tmpb->v)
				{
					i++;
					tmpb = tmpb->nx;
				}
				*/
				//fprintf(stderr, "in the bigger than end condition\n");
			}
			else if (sa->v < (getend(&tmpb)->v) && sa->v < tmpb->v)
			{
				while (sa->v < tmpb->v)
				{
					tmpb = tmpb->nx;
					i++;
				}
				while (sa->v > tmpb->v)
				{
					i++;
					tmpb = tmpb->nx;
				}
				//i++;
			}
			else
			{
				while (sa->v > tmpb->v )
				{
					i++;
					tmpb = tmpb->nx;
				}
			}
			sa->mbf = i;
			sa->mbr = (stacklen(sb)) - i;
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
	//SEPERATE THSI FUNCITON
	//function here to rotate the stack pre-pop
	//fprintf(stderr, "dir:%d, b:%d, a:%d, moves:%d\n", dir, b, a, moves);
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
		//fprintf(stderr, "after insert best decision iteration\n");
		//debug_pstacks(*sa, *sb);
	}
	updateretstack(ret, PB, sa, sb);
	//fprintf(stderr, "after insert best pop to b\n");
	//debug_pstacks(*sa, *sb);
}

void	insertbestrev(t_stack **sa, t_stack **sb, t_out *ret)
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
	//fprintf(stderr, "dir:%d, b:%d, a:%d, moves:%d\n", dir, b, a, moves);
	while (moves)
	{
		if (dir < 0)
		{
			if (b > 0 & a > 0)
				updateretstackrev(ret, RRR, sa, sb);
			else if (b > 0)
				updateretstackrev(ret, RRA, sa, sb);
			else if (a > 0)
				updateretstackrev(ret, RRB, sa, sb);
		}
		else if (dir > 0)
		{
			if (b > 0 & a > 0)
				updateretstackrev(ret, RR, sa, sb);
			else if (b > 0)
				updateretstackrev(ret, RA, sa, sb);
			else if (a > 0)
				updateretstackrev(ret, RB, sa, sb);
		}
		if (ordered(*sa))
			return ;
		a--;
		b--;
		moves--;
		//fprintf(stderr, "after insert best decision iteration\n");
		//debug_pstacks(*sa, *sb);
	}
	updateretstackrev(ret, PA, sa, sb);
	//fprintf(stderr, "after insert best pop to b\n");
	//debug_pstacks(*sa, *sb);
}

int	threesort(t_stack **sa, t_stack **sb, t_out *ret)
{

	if (stacklen(*sa) != 3)
		return (0);
	if ((*sa)->v == getlargest(*sa) && ((*sa)->nx)->v < (getend(sa))->v)
		return (1);
	else if ((*sa)->v > ((*sa)->nx)->v)
		updateretstack(ret, SA, sa, sb);
	else if ((*sa)->v == getsmallest(*sa) && ((*sa)->nx)->v == getlargest(*sa))
		updateretstack(ret, SA, sa, sb);

	//fprintf(stderr, "FIRED THREESORT\n");

	return (1);
}

void	fortysort(t_stack **sa, t_stack **sb, t_out *ret)
{
	int i;

	//debug_pstacks(*sa, *sb);
	i = 0;
	if (aassigngroups(sa) == 1)
		return ;
	while (*sa)
	{
		astructmoves(*sa);
		bstructmoves(*sa, *sb);
		movedir(*sa);
		insertbest(sa, sb, ret);

		if (threesort(sa, sb, ret) || almostordered(*sa))
		{
			//fprintf(stderr, "BEGIN 2nd PART: ALMOST ORDERED LOOKS LIKE:\n\n");
			//debug_pstacks(*sa, *sb);

			//fprintf(stderr, "\n\n");

			while (*sb)
			{
				astructmoves(*sb);
				bstructmovesrev(*sb, *sa);
				movedir(*sb);
				//fprintf(stderr, "REV BSTRUCT MOVES:\n\n");
				//debug_pstacks(*sb, *sa);
				insertbestrev(sb, sa, ret);
			}

			//fprintf(stderr, "after merge loop looks like:\n\n");
			//debug_pstacks(*sa, *sb);
			//MERGETWO SOLUTION
			//mergetwo(sa, sb, ret);
			rotcor(ret, sa, sb, 0);
			//fprintf(stderr, "after rot cor looks like:\n\n");
			//debug_pstacks(*sa, *sb);
			break;
		}
	}
}





//ADD IN LESS THAN 3 ODERING OP







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
