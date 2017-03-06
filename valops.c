#include <pushswap.h>
#include <libft.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <limits.h>

int		notgetop(t_op *list, char *line)
{
	if (!(ft_strcmp(line, "sa")))
		list->fp = &fsa;
	else if (!(ft_strcmp(line, "sb")))
		list->fp = &fsb;
	else if (!(ft_strcmp(line, "ss")))
		list->fp = &fss;
	else if (!(ft_strcmp(line, "pa")))
		list->fp = &fpa;
	else if (!(ft_strcmp(line, "pb")))
		list->fp = &fpb;
	else if (!(ft_strcmp(line, "ra")))
		list->fp = &fra;
	else if (!(ft_strcmp(line, "rb")))
		list->fp = &frb;
	else if (!(ft_strcmp(line, "rr")))
		list->fp = &frr;
	else if (!(ft_strcmp(line, "rra")))
		list->fp = &frra;
	else if (!(ft_strcmp(line, "rrb")))
		list->fp = &frrb;
	else if (!(ft_strcmp(line, "rrr")))
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
			write(2, "Error\n", 6);
			exit(1);
		}
		list->next = opsinit();
		prev = list;
		list = list->next;
	}
	free(list);
	prev->next = NULL;
	return (begin);
}
