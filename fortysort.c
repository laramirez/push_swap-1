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

//above here calculates moves for a and b

/*
void	movedirold(t_stack *sa)
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
*/

void	movedir(t_stack *sa)
{
	int bothforward;
	int bothreverse;
	int afbr;
	int arbf;

	while (sa)
	{
		bothforward = ((sa->maf > sa->mbf) ? sa->maf : sa->mbf);
		bothreverse = ((sa->mar > sa->mbr) ? sa->mar : sa->mbr);
		afbr = sa->maf + sa->mbr;
		arbf = sa->mar + sa->mbf;

		if (bothforward <= bothreverse && bothforward <= afbr &&
			   bothforward <= arbf)
		{
			sa->moves = bothforward;
			sa->dir = 1;
		}
		else if (bothreverse <= bothforward && bothreverse <= afbr &&
			   bothreverse <= arbf)
		{
			sa->moves = bothreverse;
			sa->dir = 2;
		}
		else if (afbr <= bothforward && afbr <= bothreverse &&
			   afbr <= arbf)
		{
			sa->moves = afbr;
			sa->dir = 3;
		}
		else if (arbf <= bothreverse && arbf <= bothforward &&
			   arbf <= afbr)
		{
			sa->moves = arbf;
			sa->dir = 4;
		}
		sa = sa->nx;
	}
}

void	prepoprot(t_stack *target, t_stack **sa, t_stack **sb, t_out *ret)
{
	int moves;
	int a;
	int b;

	moves = target->moves;

	while (moves)
	{
		if (target->dir == 1)
		{
			a = target->maf;
			b = target->mbf;
			if (b > 0 & a > 0)
				updateretstack(ret, RR, sa, sb);
			else if (b > 0)
				updateretstack(ret, RB, sa, sb);
			else if (a > 0)
				updateretstack(ret, RA, sa, sb);
			target->maf -= 1;
			target->mbf -= 1;
		}
		else if (target->dir == 2)
		{
			a = target->mar;
			b = target->mbr;
			if (b > 0 & a > 0)
				updateretstack(ret, RRR, sa, sb);
			else if (b > 0)
				updateretstack(ret, RRB, sa, sb);
			else if (a > 0)
				updateretstack(ret, RRA, sa, sb);
			target->mar -= 1;
			target->mbr -= 1;
		}
		else if (target->dir == 3)
		{
			a = target->maf;
			b = target->mbr;
			if (b > 0 & a > 0)
			{
				updateretstack(ret, RA, sa, sb);
				updateretstack(ret, RRB, sa, sb);
			}
			else if (b > 0)
				updateretstack(ret, RRB, sa, sb);
			else if (a > 0)
				updateretstack(ret, RA, sa, sb);
			target->maf -= 1;
			target->mbr -= 1;
		}
		else if (target->dir == 4)
		{
			a = target->mar;
			b = target->mbf;
			if (b > 0 & a > 0)
			{
				updateretstack(ret, RRA, sa, sb);
				updateretstack(ret, RB, sa, sb);
			}
			else if (b > 0)
				updateretstack(ret, RB, sa, sb);
			else if (a > 0)
				updateretstack(ret, RRA, sa, sb);
			target->mar -= 1;
			target->mbf -= 1;
		}
		if (ordered(*sa))
			return ;
		moves--;
		//fprintf(stderr, "after insert best decision iteration\n");
		//debug_pstacks(*sa, *sb);
	}


}

void	insertbest(t_stack **sa, t_stack **sb, t_out *ret)
{
	t_stack *tmp;
	t_stack *target;
	int moves;

	//get t_stack taht has the minimum number of moves
	tmp = *sa;
	target = tmp;
	moves = tmp->moves;
	while (tmp)
	{
		if (tmp->moves < moves)
		{
			moves = tmp->moves;
			target = tmp;
		}
		tmp = tmp->nx;
	}

	prepoprot(target, sa, sb, ret);
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

int numsort(t_stack **sa, t_stack **sb, t_out *ret, int size)
{
	int i;
	int num;

	i = 0;
	num = size;
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
	int len;

	if (aassigngroups(sa) == 1)
		return ;
	i = 0;
	len = 3;
	if (stacklen(*sa) > 101)
		len = 7;
	while (*sa)
	{
		if (almostordered(*sa) || numsort(sa, sb, ret, len))
			{
				rotcor(ret, sa, sb, 0);
				mergetwo(sa, sb, ret);
				rotcor(ret, sa, sb, 0);
				break;
			}
		astructmoves(*sa);
		bstructmoves(*sa, *sb);
		movedir(*sa);
		insertbest(sa, sb, ret);
/*
		if (almostordered(*sa) || numsort(sa, sb, ret, len))
			{
				rotcor(ret, sa, sb, 0);
				mergetwo(sa, sb, ret);
				rotcor(ret, sa, sb, 0);
				break;
			}
*/
	}
}
