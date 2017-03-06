/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstruct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 10:22:44 by mgould            #+#    #+#             */
/*   Updated: 2017/03/05 10:39:55 by mgould           ###   ########.fr       */
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
