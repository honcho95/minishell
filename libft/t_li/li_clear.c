/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:19:08 by enolbas           #+#    #+#             */
/*   Updated: 2022/11/10 19:44:52 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	li_clear(t_li **lst)
{
	t_li	**copyli;
	t_li	*copyli_two;

	copyli = lst;
	if (!*lst)
		return ;
	while (*copyli)
	{
		copyli_two = (*copyli)->next;
		(*copyli)->content_one = -2;
		(*copyli)->content_two = -2;
		(*copyli)->content_three = -2;
		(*copyli)->content_four = -2;
		(*copyli)->content_five = -2;
		free(*copyli);
		*copyli = copyli_two;
	}
	*lst = NULL;
}
