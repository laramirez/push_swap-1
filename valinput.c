/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valinput.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 10:43:26 by mgould            #+#    #+#             */
/*   Updated: 2017/03/05 20:41:06 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>

int		validnumbers(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		if (ps_big_atoi(av[i]) > INT_MAX || ps_big_atoi(av[i]) < INT_MIN)
		{
			return (0);
		}
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == ' ')
				;
			else if (!ft_isdigit(av[i][j]))
			{
				if (!(av[i][j] == '-' && ft_isdigit(av[i][j + 1])))
				{
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

//problem is i'm getting a dumb list and i have to split it up somehow.
//and it fucking sucks
//
t_stack	*makestack(char **av)
{
	int		i;
	int		j;
	char	**tmp;
	t_stack *stack;
	t_stack *begin;

	i = 1;
	stack = stackinit();
	begin = stack;
	while (av[i])
	{
		tmp = ft_strsplit(av[i], ' ');
		j = 0;
		while (tmp[j])
		{
			stack->v = (int)ps_big_atoi(*tmp);
			stack->nx = stackinit();
			(stack->nx)->pv = stack;
			stack = stack->nx;
			j++;
			ft_printf("%s\n", tmp);
			sleep(1);
		}
		//stack->v = (int)ps_big_atoi(*tmp);
		if (!av[i + 1])
			return (begin);
	//	stack->nx = stackinit();
	//	(stack->nx)->pv = stack;
	//	stack = stack->nx;
		i++;
	}
	return (begin);
}

t_stack	*valinput(int ac, char **av, t_stack *stacka)
{
	int	len;

	len = 0;
	while (av[len])
		len++;
	if (ac < 2)
	{
		return (NULL);
	}
	if (!validnumbers(av))
	{
		write(2, "Error\n", 6);
		return (NULL);
	}
	stacka = makestack(av);
	return (stacka);
}
