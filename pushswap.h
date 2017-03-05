/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:06:08 by mgould            #+#    #+#             */
/*   Updated: 2017/03/04 19:17:50 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

typedef enum s_optype {sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr, nothing} t_optype;

typedef struct	s_stack
{
	int				v;
	struct s_stack	*pv;
	struct s_stack	*nx;
}				t_stack;

typedef struct	s_op
{
	t_optype		op;
	void			(*fp)(t_stack **stacka, t_stack **stackb);
	struct s_op		*next;
}				t_op;

t_op			*opsinit();
t_stack			*stackinit();
t_op			*getoplist();
int				validnumbers(char **av);
t_stack			*makestack(char **av);
t_stack			*valinput(int ac, char **av, t_stack *stacka);
int				notgetop(t_op *list, char *line);
void			debug_pstacks(t_stack *stacka, t_stack *stackb);
void			process_op(t_stack **stacka, t_stack **stackb, t_op *list);
/*
** operation functions
*/
void			fsa(t_stack **stacka, t_stack **stackb);
void			fsb(t_stack **stacka, t_stack **stackb);
void			fpa(t_stack **stacka, t_stack **stackb);
void			fpb(t_stack **stacka, t_stack **stackb);

/*
void			fss(t_stack **stacka, t_stack **stackb);
void			fra(t_stack **stacka, t_stack **stackb);
void			frb(t_stack **stacka, t_stack **stackb);
void			frr(t_stack **stacka, t_stack **stackb);
void			frra(t_stack **stacka, t_stack **stackb);
void			frrb(t_stack **stacka, t_stack **stackb);
void			frrr(t_stack **stacka, t_stack **stackb);
*/
#endif
