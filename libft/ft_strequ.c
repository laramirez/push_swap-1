/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 08:09:32 by mgould            #+#    #+#             */
/*   Updated: 2016/12/02 16:10:44 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strequ(char const *s1, char const *s2)
{
	int i;

	if (!s1 || !s2)
		return (0);
	i = ft_strcmp((char *)s1, (char *)s2);
	if (i == 0)
		return (1);
	else
		return (0);
}