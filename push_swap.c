#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>
//
#include <stdio.h>

int main(int ac, char **av)
{
	t_stack	*stacka;
	t_stack *stackb;
	t_out	*ret;

	//sleep(1);
	stacka = NULL;
	stackb = NULL;
	ret = outinit();
	if (!(stacka = valinput(ac, av, stacka)))
			return (0);
	//SORTING ALGO
	//stim(&stacka, &stackb, ret);
	fortysort(&stacka, &stackb, ret);
	//PRINT OPS AND OPS NUMBER OF OPS
	//fprintf(stderr, "ret number is %d\n", retnumber(ret));
	printret(ret);

	//IMPLEMENT DEBUG -V -C -VC FUNCTION HERE TO PRINT IT OUT
	return (0);
}


















