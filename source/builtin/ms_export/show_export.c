/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:32:24 by enolbas           #+#    #+#             */
/*   Updated: 2022/12/07 15:36:03 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

int	show_export(t_input *input)
{
	t_ls	*copy;
	char	*after_equal;
	int		pos;

	copy = input->export;
	if (!copy || !(copy->content_one) || !*(copy->content_one))
		return (0);
	while (copy)
	{
		after_equal = ft_strchr(copy->content_one, '=');
		if (after_equal)
			after_equal += 1;
		pos = my_strchr_pos(copy->content_one, '=');
		if (pos > -1)
		{
			copy->content_one[pos] = 0;
			ft_printf("export %s=", copy->content_one);
			copy->content_one[pos] = '=';
			ft_printf("\"%s\"\n", after_equal);
		}
		else
			ft_printf("export %s\n", copy->content_one);
		copy = copy->next;
	}
	return (0);
}
