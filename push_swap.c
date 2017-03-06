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

	stacka = NULL;
	if (!(stacka = valinput(ac, av, stacka)))
			return (0);
	while (stacka)
	{
		ft_printf("%d\n", stacka->v);
		stacka = stacka->nx;
	}
	return (0);
}
