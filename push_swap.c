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

static int	aassigngroups(t_stack **stack)
{
	int i;
	int tmp;
	t_stack *stemp;

	if (!(*stack))
		return (0);
	stemp = *stack;
	tmp = (stemp)->v;
	i = 1;
	while (stemp)
	{
		if ((stemp)->v >= tmp)
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
	return (i);
}

static int	bassigngroups(t_stack **stack)
{
	int i;
	int tmp;
	t_stack *stemp;

	if (!(*stack))
		return (0);
	i = 1;
	stemp = *stack;
	tmp = (stemp)->v;
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
	return (i);
}


void	mergestack(t_stack **sa, t_stack **sb, int *count)
{
	t_stack *tmpb;
	int		group;

	group = (*sb)->g;
	tmpb = *sb;
	//handles the case where the list is only 1 long. . .
	while (tmpb->v < (tmpb->nx)->v)
	{
		printf("mergestack:fsb\n");
		fsb(sa, sb);
		*count += 1;
		if (revordered(*sb))
		{
			bassigngroups(sb);
			debug_pstacks(*sa, *sb);
			break;
		}
		debug_pstacks(*sa, *sb);
		frb(sa, sb);
		printf("mergestack:frb\n");
		debug_pstacks(*sa, *sb);
		*count += 1;
	}
}


void	initsets(t_stack **sa, t_stack **sb)
{
	t_stack *end;
	int count;

	count = 0;
	end = getend(sa);
	if (aassigngroups(sa) == 1)
		return ;
	//if only one group, it's already ordered!
	while (*sa)
	{
		usleep(300000);
		if ((!(*sa)->nx) || ((*sa)->v < end->v && (*sa)->v < ((*sa)->nx)->v))
		{

			printf("you are in comp for group 2\n");
			if ((*sb) && (*sa)->v < (*sb)->v && bassigngroups(sb) > 1)
			{
				printf("you are here\n");
				mergestack(sa, sb, &count);
				//check the merge size, will have to
				//pass variable to this function.  this is the Tim Sort part
			}
			printf("two:fpb\n");
			fpb(sa, sb);
		}
		else if (((*sa)->nx)->v < (end)->v && ((*sa)->nx)->v < (*sa)->v)
		{
			printf("three:fsa\n");
			fsa(sa, sb);
		}
		else if ((((stacklen(*sa) == 1) && (end->v < (*sa)->v))) ||
				(end->v < (*sa)->v && (end)->v <= ((*sa)->nx)->v))
		{
			printf("four:frra\n");
			frra(sa, sb);
		}


		if((*sb) && (*sb)->v < ((getend(sb))->v))
		{
			frb(sa, sb);
			count++;
		}
		count++;
		aassigngroups(sa);
		debug_pstacks(*sa, *sb);
		end = getend(sa);
		if (ordered(*sa))
		{
			// EASY WIN IS HERE, IF THERE ARE ONLY 2 GROUPS WHEN SA IS
			// ORDERED, THEN YOU DESIGN FUNCTION TO INSERT ON SORTED
			// LIST INTO ANOTHER - CAN USE THIS IN OTHER FUNCTIONS TO
			// SOLVE THIS THING!
			//improve mergestack so it handles more thhna just the first
			//variable.  it handles whole list.
			//also fix so that it combines to the right sizes, including
			//the list on the left side.  decide how you will fit into
			//the list on the left sid.
			//think about if you have an odd number of groups, etc.
			mergestack(sa, sb, &count);

			//if there are only 2 groups total, do the merge.
			break;
			//this is where the tim logic comes in.
		}
	}
	printf("ops count is %d\n", count);
}

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
	int		minrun;
	int		i;

	i = 32;
	stacka = NULL;
	stackb = NULL;
	if (!(stacka = valinput(ac, av, stacka)))
			return (0);
	len = stacklen(stacka);
	if (len < 65)
		minrun = len;
	else
		while ((minrun = (len / i)) > 64)
		{
			i *= 2;
		}

	printf("I is:%d, minrun is:%d", i, minrun);
/*
minrun is chosen from the range 32 to 64 inclusive, such that the size of the data, divided by minrun, is equal to, or slightly smaller than, a power of two.
*/
	printf("stacklen:%d\n", len);
	smerge(&stacka, &stackb, len);
	return (0);
}


















