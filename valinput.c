/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valinput.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 10:43:26 by mgould            #+#    #+#             */
/*   Updated: 2017/02/24 10:47:30 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>

int	validnumbers(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		if (ps_big_atoi(av[i]) > INT_MAX || ps_big_atoi(av[i]) < INT_MIN)
			return (0);
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_stack *makestack(char **av)
{
	int i;
	t_stack *stack;
	t_stack *begin;

	i = 1;
	stack = stackinit();
	begin = stack;
	while(av[i])
	{
		stack->v = (int)ps_big_atoi(av[i]);
		if (!av[i + 1])
			return (begin);
		stack->nx = stackinit();
		stack = stack->nx;
		i++;
	}
	return (begin);
}

t_stack *valinput(int ac, char **av, t_stack *stacka)
{
	int	len;

	len = 0;
	while (av[len])
		len++;
	if (ac < 2)
	{
		//delete this to display nothing
		ft_putstr("enter in a sequence of nubmers");
		return (NULL);
	}
	if (!validnumbers(av))
	{
		write(1, "Error\n", 6);
		return (NULL);
	}
	stacka = makestack(av);
	return (stacka);
}
