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

	if (!(*stack))
		return (NULL);
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
	while (*sa)
	{
		sleep(1);
		if ((!(*sa)->nx))
		{
			printf("one:fpb\n");
			fpb(sa, sb);
		}
		else if ((*sa)->v < end->v && (*sa)->v < ((*sa)->nx)->v)
		{
			printf("two:fpb\n");
			fpb(sa, sb);
		}
		else if (((*sa)->nx)->v < (end)->v && ((*sa)->nx)->v < (*sa)->v)
		{
			printf("three:fsa\n");
			fsa(sa, sb);
		}
		else if ((( (stacklen(*sa) == 1) && (end->v < (*sa)->v))) ||
				(end->v < (*sa)->v && (end)->v <= ((*sa)->nx)->v))
		{
			printf("four:frra\n");
			frra(sa, sb);
		}
		else
		{
			printf("five:fpb\n");
			fpb(sa, sb);
		}

		if ((*sb)->nx && ((*sb)->v < ((*sb)->nx)->v))
		{
			if((*sb)->v < ((getend(sb))->v))
				frb(sa, sb);
			else
				fsb(sa, sb);
			count++;
		}
		count++;

		bassigngroups(sb);
//		print out groups! for debugging!
		debug_pstacks(*sa, *sb);
		end = getend(sa);
		//if 2 groups, then return
		//check rotational polarity as an end condition.
		//rotational polarity A, . . B, then rotate and fix it adding ops, break,
		//and return.
		//although rotational polarity is probably more like group polarity.
		//like "if total number of groups is 2 then you have rotational polarity.
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
	debug_pstacks(*stacka, *stackb);
	printf("*****************\n");
	initsets(stacka, stackb);
}

int main(int ac, char **av)
{
	t_stack	*stacka;
	t_stack *stackb;
	int		len;

	printf("you are fuckikng here \n\n");
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
