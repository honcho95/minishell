/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_er.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 04:28:25 by enolbas           #+#    #+#             */
/*   Updated: 2022/12/17 04:28:45 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

int	ret_er(t_redir *redir, int res)
{
	if (res < 0)
	{
		perror(redir->file);
		return (-1);
	}
	return (0);
}
