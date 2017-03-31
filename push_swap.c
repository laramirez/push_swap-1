#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>

int main(int ac, char **av)
{
	t_stack	*stacka;
	t_stack *stackb;
	t_out	*ret;

	stacka = NULL;
	stackb = NULL;
	ret = outinit();
	if (!(stacka = valinput(ac, av, stacka)))
			return (0);
	fortysort(&stacka, &stackb, ret);
	printret(ret);
	return (0);
}
