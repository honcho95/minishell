/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_add_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:18:44 by enolbas           #+#    #+#             */
/*   Updated: 2022/11/25 10:04:58 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ls_add_back(t_ls **lst, t_ls *new)
{
	t_ls	*copyl;

	if (!new)
		return (1);
	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			copyl = ls_last(*lst);
			copyl->next = new;
			copyl->next->prev = copyl;
		}
	}
	return (0);
}
