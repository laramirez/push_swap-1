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
		if (wheredestj(*sb, tmp) >= 0)
			while ((*sb)->v != tmp)
				updateretstack(ret, RB, sa, sb);
		else
			while ((*sb)->v != tmp)
				updateretstack(ret, RRB, sa, sb);
	}
	else
	{
		tmp = getsmallest(*sa);
		if (wheredestj(*sa, tmp) >= 0)
			while ((*sa)->v != tmp)
				updateretstack(ret, RA, sa, sb);
		else
			while ((*sa)->v != tmp)
			{
				//fprintf(stderr, "in rot cor last while:\n\n");
				updateretstack(ret, RRA, sa, sb);
				//debug_pstacks(*sa, *sb);
			}
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

	if (!(sb))
		return ;
	while (sa)
	{
		i = 0;
		tmpb = sb;
		if (sa->v < (getend(&tmpb)->v) && sa->v > tmpb->v)
		{
			;
		}
		else if (sa->v > getlargest(sb))
		{
			while (tmpb->v != getlargest(sb))
			{
				i++;
				tmpb = tmpb->nx;
			}
		}
		else if (sa->v < getsmallest(sb))
		{
			i++;
			while (tmpb->v != getsmallest(sb))
			{
				i++;
				tmpb = tmpb->nx;
			}
		}
		else if (sa->v > (getend(&tmpb)->v) && sa->v > tmpb->v)
		{
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
		else
		{
			while (sa->v < tmpb->v )
			{
				i++;
				tmpb = tmpb->nx;
			}
		}
		sa->mbf = i;
		sa->mbr = (stacklen(sb)) - i;
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
}


void	mergetwo(t_stack **sa, t_stack **sb, t_out *ret)
{
	while (*sb)
	{
		if ((*sb)->v > getlargest(*sa))
		{
			rotcor(ret, sa, sb, 0);
			updateretstack(ret, PA, sa, sb);
		}
		else if ((*sb)->v < getsmallest(*sa))
		{
			rotcor(ret, sa, sb, 0);
			updateretstack(ret, PA, sa, sb);
		}
		else if ((*sb)->v > (*sa)->v )//&& (!(((*sb)->v) > getlargest(*sa))))
			updateretstack(ret, RA, sa, sb);
		else if ((*sb)->v < (*sa)->v && (*sb)->v > (getend(sa))->v)
			updateretstack(ret, PA, sa, sb);
		else
			updateretstack(ret, RRA, sa, sb);
		//this look slike it just reverse rotates by default instead of goes to
		//the right place to insert
	}
}

int	threesort(t_stack **sa, t_stack **sb, t_out *ret)
{

	if (stacklen(*sa) != 3)
		return (0);

	//debug_pstacks(*sa, *sb);
	if ((*sa)->v == getlargest(*sa) && ((*sa)->nx)->v < (getend(sa))->v)
		return (1);
	else if ((*sa)->v > ((*sa)->nx)->v)
		updateretstack(ret, SA, sa, sb);
	else if ((*sa)->v == getsmallest(*sa) && ((*sa)->nx)->v == getlargest(*sa))
		updateretstack(ret, SA, sa, sb);

	//fprintf(stderr, "AFTER THREE SORT FIRED sort:\n\n");
	//debug_pstacks(*sa, *sb);
	return (1);
}

//can pick the size on numsort to make it a bit faster

int numsort(t_stack **sa, t_stack **sb, t_out *ret)
{
	int i;
	int num;

	i = 0;
	num = 3;
	if (stacklen(*sa) != num)
		return (0);
	//fprintf(stderr, "NUM SORT FIRED sort:\n\n");
	//debug_pstacks(*sa, *sb);
	while (i < (num - 3))
	{
		rotcor(ret, sa, sb, 0);
		updateretstack(ret, PB, sa, sb);
		i++;
	}
	//fprintf(stderr, "Before 3 sort:\n\n");
	//debug_pstacks(*sa, *sb);
	threesort(sa, sb, ret);
	i = 0;
	while (i < (num - 3))
	{
		rotcor(ret, sa, sb, 0);
		updateretstack(ret, PA, sa, sb);
		i++;
	}

	return (1);
}


void	fortysort(t_stack **sa, t_stack **sb, t_out *ret)
{
	int i;

	i = 0;
	if (aassigngroups(sa) == 1)
		return ;
//	fprintf(stderr, "BEGIN:\n\n");
//f	debug_pstacks(*sa, *sb);
	while (*sa)
	{
		astructmoves(*sa);
		bstructmoves(*sa, *sb);
		movedir(*sa);
		//
		//debug_pstacks(*sa, *sb);
		//
		insertbest(sa, sb, ret);

		if (almostordered(*sa) || numsort(sa, sb, ret))// || almostordered(*sa))
		{
			rotcor(ret, sa, sb, 0);
			//debug_pstacks(*sa, *sb);

			//MERGETWO SOLUTION
			mergetwo(sa, sb, ret);
			//fprintf(stderr, "after merge two:\n\n");
			//debug_pstacks(*sa, *sb);
			rotcor(ret, sa, sb, 0);
			//fprintf(stderr, "AT END:\n\n");
			//debug_pstacks(*sa, *sb);
			break;
		}
	}
}


