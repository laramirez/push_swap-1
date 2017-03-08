#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>
//
#include <stdio.h>

static int	stacklen(t_stack *stack)
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

static t_stack	*getend(t_stack **stack)
{
	t_stack *end;

	end = *stack;
	while (end->nx)
		end = end->nx;
	return (end);
}

static void		bassigngroups(t_stack **stack)
{
	int i;
	int tmp;
	t_stack *stemp;

	if (!(*stack))
		return ;
	stemp = *stack;
	tmp = (stemp)->v;
	i = 1;
	while (stemp)
	{
		if ((stemp)->v <= tmp)
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
}

void	initsets(t_stack **sa, t_stack **sb)
{
	t_stack *end;
	int count;

	count = 0;
	end = getend(sa);
	debug_pstacks(*sa, *sb);
	while (*sa)
	{
		printf("top\n");
		printf("what is happening\n");
		debug_pstacks(*sa, *sb);
		sleep(1);
		if ((!(*sa)->nx))
		{
			printf("one\n");
			fpb(sa, sb);
		}
		else if ((*sa)->v < end->v && (*sa)->v < ((*sa)->nx)->v)
		{
			printf("two\n");
			fpb(sa, sb);
		}
		else if (((*sa)->nx)->v < (end)->v && ((*sa)->nx)->v < (*sa)->v)
		{
			printf("three\n");
			fsa(sa, sb);
		}
		else if ((( (stacklen(*sa) == 2) && (end->v < (*sa)->v))) ||
				(end->v < (*sa)->v && (end)->v <= ((*sa)->nx)->v))
		{
			printf("four\n");
			frra(sa, sb);
			printf("four after rotate\n");
			debug_pstacks(*sa, *sb);
			fpb(sa, sb);
			printf("four after push to b\n");
			debug_pstacks(*sa, *sb);
			count++;
		}
		else
		{
			printf("five\n");
			fpb(sa, sb);
		}

		if ((*sb)->nx && ((*sb)->v < ((*sb)->nx)->v))
		{
			printf("you got here\n");
			if((*sb)->v < ((getend(sb))->v))
				frb(sa, sb);
			else
				fsb(sa, sb);
			count++;
		}
		printf("past if else\n");
		count++;
		bassigngroups(sb);
		printf("past assign groups\n");

		debug_pstacks(*sa, *sb);
		printf("past debug pstacks\n");
		end = getend(sa);
		printf("past getend\n");
	}
	printf("ops count is %d\n", count);
	//assign groups after the sort.
}

/*
void	sets(t_stack **sa, t_stack **sb)
{
	int groups;
	t_stack *tmp;

	groups = 0;
	ft_printf("groups is:%d\n", groups);
	if (*sa)
		tmp = *sa;
	else
		tmp = *sb;
	while (tmp)
	{


		printf("tmp->v:%d\n", tmp->v);
		tmp = tmp->nx;
	}
}
*/

void	smerge(t_stack **stacka, t_stack **stackb, int len)
{
	int i;
	//int tmp;

	i = 0;
	if (len <= 1)
	{
		ft_printf("early return\n");
		return ;
	}
	initsets(stacka, stackb);
}

int main(int ac, char **av)
{
	t_stack	*stacka;
	t_stack *stackb;
	int		len;

	stacka = NULL;
	stackb = NULL;
	if (!(stacka = valinput(ac, av, stacka)))
			return (0);
	len = stacklen(stacka);
	printf("stacklen:%d\n", len);
	//do some checks here
	//is it already sorted?
	//can it be solved by rotation?
	//is it less than X?
	smerge(&stacka, &stackb, len);


	return (0);
}



/*
static int	depth(int len)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (i < len)
	{
		i *= 2;
		j++;
	}
	return (j);
}
*/



//lookup first element of next group.
//if else function to pop correclty to other function.
//think if you have to do some mod thing to check groups.
////potentially update group numbers to avoid dump mod thing
//as you move groups over
//you can update the number of groups each time you call this funciton.
//as long as you rotate all the way through, groups will retain
//relative order
//set them into groups of at least 2 to start, using the 4 sort trick.
//then compare adjacent groups

/*
static int	pairs(t_stack **sa, t_stack **sb)
{
	//make helper functions and norm this gigantic mess AFTER
	//you confirm that it will work :-)
	int i;

	i = 0;
	ft_printf("in pairs\n");
	while ((*sa) && (*sa)->nx && ((*sa)->nx)->nx && (((*sa)->nx)->nx)->nx)
	{
		ft_printf("inside while\n");
		i++;
		fpb(sa, sb);
		fpb(sa, sb);
		(*sb)->g = i;
		((*sb)->nx)->g = i;

		if ((*sa)->v > ((*sa)->nx)->v && (*sb)->v < ((*sb)->nx)->v)
			fss(sa, sb);
		else if ((*sa)->v > ((*sa)->nx)->v  )
			fsa(sa, sb);
		else if ((*sb)->v < ((*sb)->nx)->v )
			fsb(sa, sb);
		i++;
		fpb(sa, sb);
		fpb(sa, sb);
		(*sb)->g = i;
		((*sb)->nx)->g = i;
	}
	while ((*sa) && (*sa)->nx)
	{
		if ((*sa)->v > ((*sa)->nx)->v  )
			fsa(sa, sb);
		i++;
		fpb(sa, sb);
		fpb(sa, sb);
		(*sb)->g = i;
		((*sb)->nx)->g = i;
	}
	if ((*sa))
	{
		i++;
		fpb(sa, sb);
		(*sb)->g = i;
	}
	return (i);
}
*/

