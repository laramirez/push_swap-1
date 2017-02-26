/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstruct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 10:22:44 by mgould            #+#    #+#             */
/*   Updated: 2017/02/26 08:12:27 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>

t_op	*opsinit(void)
{
	t_op *list;

	list = (t_op *)(malloc(sizeof(t_op)));
	list->op = nothing;
	list->next = NULL;
	return (list);
}

t_stack	*stackinit(void)
{
	t_stack *stack;

	stack = (t_stack *)(malloc(sizeof(t_stack)));
	stack->pv = NULL;
	stack->nx = NULL;
	return (stack);
}

int		notgetop(t_op *list, char *line)
{
	if (!(strcmp(line, "sa")))
		list->op = sa;
	else if (!(strcmp(line, "sb")))
		list->op = sb;
	else if (!(strcmp(line, "ss")))
		list->op = ss;
	else if (!(strcmp(line, "pa")))
		list->op = pa;
	else if (!(strcmp(line, "pb")))
		list->op = pb;
	else if (!(strcmp(line, "ra")))
		list->op = ra;
	else if (!(strcmp(line, "rb")))
		list->op = rb;
	else if (!(strcmp(line, "rr")))
		list->op = rr;
	else if (!(strcmp(line, "rra")))
		list->op = rra;
	else if (!(strcmp(line, "rrb")))
		list->op = rrb;
	else if (!(strcmp(line, "rrr")))
		list->op = rrr;
	else
		return (1);
	return (0);
}

t_op	*getoplist(void)
{
	char	*line;
	t_op	*list;
	t_op	*begin;
	t_op	*prev;

	line = NULL;
	list = opsinit();
	begin = list;
	prev = list;
	while (get_next_line(0, &line))
	{
		if (notgetop(list, line))
		{
			ft_printf("KO\n");
			return (0);
		}
		list->next = opsinit();
		prev = list;
		list = list->next;
	}
	free(list);
	prev->next = NULL;
	return (begin);
}
