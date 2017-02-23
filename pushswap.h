/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:06:08 by mgould            #+#    #+#             */
/*   Updated: 2017/02/22 16:32:42 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

typedef enum s_optype {sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr, nothing} t_optype;

typedef struct	s_op
{
	t_optype		op;
	struct s_op		*next;
}				t_op;

typedef struct	s_stack
{
	int				v;
	struct s_stack	*pv;
	struct s_stack	*nx;
}				t_stack;

#endif
