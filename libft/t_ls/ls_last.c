/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:52:12 by enolbas           #+#    #+#             */
/*   Updated: 2022/06/19 11:17:34 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_ls	*ls_last(t_ls *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
