/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstruct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 10:22:44 by mgould            #+#    #+#             */
/*   Updated: 2017/03/04 22:40:07 by mgould           ###   ########.fr       */
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
	list->fp = NULL;
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
		list->fp = &fsa;
	else if (!(strcmp(line, "sb")))
		list->fp = &fsb;
	else if (!(strcmp(line, "ss")))
		list->fp = &fss;
	else if (!(strcmp(line, "pa")))
		list->fp = &fpa;
	else if (!(strcmp(line, "pb")))
		list->fp = &fpb;
	else if (!(strcmp(line, "ra")))
		list->fp = &fra;
	else if (!(strcmp(line, "rb")))
		list->fp = &frb;
	else if (!(strcmp(line, "rr")))
		list->fp = &frr;
	else if (!(strcmp(line, "rra")))
		list->fp = &frra;
	else if (!(strcmp(line, "rrb")))
		list->fp = &frrb;
	else if (!(strcmp(line, "rrr")))
		list->fp = &frrr;
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
