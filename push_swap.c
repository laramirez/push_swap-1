#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>
//
#include <stdio.h>

int	stacklen(t_stack *stack)
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
	i = -1;
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
			i--;
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
	t_stack *end;


	if (!(*sb))
		return ;
	group = (*sb)->g;
	tmpb = *sb;
	end = getend(sb);
	while ((*sb)->g == group)
	{
		fpa(sa, sb);
		*count += 1;
	}
	debug_pstacks(*sa, *sb);
	ft_putstr_color("second while of merge function-\n\n", 2);
	//may need to get the smallest and largest in group, determine where to insert.
	while ((*sa)->g == group)
	{
		//should be SIMPLE WHILE LOOP HERE TO STICK BETWEEN 2 NUMBERS!KJEE
		if ((*sa)->v < end->v)
		{
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
			//may rotate back to starting position here so it's set up right
		}
		else if ((*sa)->v > (*sb)->v && !((*sa)->v < end->v))
		{
			while ((*sa)->v > (*sb)->v && !((*sa)->v < end->v))
			{
				frrb(sa, sb);
				*count += 1;
			}
		}
		else
			fpb(sa, sb);
		*count += 1;
		end = getend(sb);
	}
	ft_putstr_color("after second while of merge function-\n\n", 2);
	debug_pstacks(*sa, *sb);
	/*
	//handles the case where the list is only 1 long. . .
	while (tmpb->v < (tmpb->nx)->v)
	{
		usleep(300000);
		printf("mergestack:fsb\n");
		fsb(sa, sb);
		*count += 1;
		bassigngroups(sb);
		debug_pstacks(*sa, *sb);
		if (revordered(*sb))
		{
			break;
		}
		frb(sa, sb);
		printf("mergestack:frb\n");
		bassigngroups(sb);
		debug_pstacks(*sa, *sb);
		*count += 1;
	}
	*/
}

//two functions
//merge stack b by itself
//merge stack a and b together
//you can remove count once you have a function that lists the operations.
//can create list of operators function whenever, right now it is count.

void	initsets(t_stack **sa, t_stack **sb)
{
	t_stack *end;
	int count;

	count = 0;
	end = getend(sa);
	while (*sa)
	{
		//remove this usleep
		usleep(300000);
		if ((!(*sa)->nx) || ((*sa)->v < end->v && (*sa)->v < ((*sa)->nx)->v))
		{

			printf("you are in comp for group 2\n");
			if ((*sb) && (*sa)->v < (*sb)->v && absolute_value(bassigngroups(sb)) > 1)
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
		bassigngroups(sb);
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
			//if there are < 2 groups total, do the merge and return
			break;
			//this is where the merge logic comes in.
		}
	}
	printf("ops count is %d\n", count);
}

void	smerge(t_stack **stacka, t_stack **stackb, int len)
{
	int i;

	i = 0;
	if (len <= 1)
	{
		ft_printf("early return\n");
		return ;
	}
	if (aassigngroups(stacka) == 1)
	{
		printf("already ordered\n");
		return ;
	}
	debug_pstacks(*stacka, *stackb);
	printf("*****************\n");
	initsets(stacka, stackb);
}

static int getminrun(t_stack *stacka)
{
	int i;
	int ret;

	ret = 0;
	//set the minimum lower boundary here, currently at 16
	i = 16;
	ret = stacklen(stacka);
	if (ret < 65)
	{
		if (ret < i && ret > 1)
			ret = i;
	}
	else
	{
		while ((ret = (ret / i)) > 64)
			i *= 2;
	}
	return (ret);
}

//to do 3.19.2017
//decide if i'm going to sort stack b as I go and that's it - no back and forth
//get it to merge in stack b, stack b + stack a (when 1 in each), so it can return
//logic here on how to merge / when to merge, like if it's bigger than a certain size;
//the lower boundary size then don't merge it, keep sorting; look for run in stack a.
//create a thing to capture the ops list
//

int main(int ac, char **av)
{
	t_stack	*stacka;
	t_stack *stackb;
	int		minrun;

	stacka = NULL;
	stackb = NULL;
	if (!(stacka = valinput(ac, av, stacka)))
			return (0);
	minrun = getminrun(stacka);
	printf("minrun is:%d\n", minrun);
/*
minrun is chosen from the range 32 to 64 inclusive, such that the size of the data, divided by minrun, is equal to, or slightly smaller than, a power of two.  However in
this case I set a lower bound of 16 since we have small data sets.  I may not need
a lower bound?
*/
	smerge(&stacka, &stackb, minrun);
	return (0);
}


















