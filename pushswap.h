/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:06:08 by mgould            #+#    #+#             */
/*   Updated: 2017/03/22 14:40:32 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

typedef enum s_optype {sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr, nothing} t_optype;

typedef enum s_onum {SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR, NOTHING} t_onum;

typedef struct	s_stack
{
	int				v;
	struct s_stack	*pv;
	struct s_stack	*nx;
	int				g;
}				t_stack;

typedef struct	s_op
{
	t_optype		op;
	void			(*fp)(t_stack **stacka, t_stack **stackb);
	struct s_op		*next;
}				t_op;

typedef struct	s_out
{
	t_onum			num;
	struct s_out	*nx;
}				t_out;

t_op			*opsinit();
t_stack			*stackinit();
t_op			*getoplist();
int				validnumbers(char **av);
t_stack			*makestack(char **av);
t_stack			*valinput(int ac, char **av, t_stack *stacka);
int				notgetop(t_op *list, char *line);
void			debug_pstacks(t_stack *stacka, t_stack *stackb);
void			process_op(t_stack **stacka, t_stack **stackb, t_op *list);
int				isrevordered(t_stack *stacka, t_stack *stackb);
int				revordered(t_stack *stackb);
int				ordered(t_stack *stackb);
t_out			*outinit();
/*
** helper functions
*/
int				stacklen(t_stack *stack);
t_stack			*getend(t_stack **stack);
int				aassigngroups(t_stack **stack);
int				bassigngroups(t_stack **stack);
int				getminrun(t_stack *stacka);
/*
** print out list from pushswap
*/
void			printoutlist(t_out *outlist);
void			printelement(t_optype num);
void			printelement2(t_onum num);
void			doop(t_onum num, t_stack **sa, t_stack **sb);
/*
** operation functions
*/
void			fsa(t_stack **stacka, t_stack **stackb);
void			fsb(t_stack **stacka, t_stack **stackb);
void			fpa(t_stack **stacka, t_stack **stackb);
void			fpb(t_stack **stacka, t_stack **stackb);
void			fss(t_stack **stacka, t_stack **stackb);
void			fra(t_stack **stacka, t_stack **stackb);
void			frb(t_stack **stacka, t_stack **stackb);
void			frr(t_stack **stacka, t_stack **stackb);
void			frra(t_stack **stacka, t_stack **stackb);
void			frrb(t_stack **stacka, t_stack **stackb);
void			frrr(t_stack **stacka, t_stack **stackb);
#endif
