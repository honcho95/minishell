/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:23:56 by enolbas           #+#    #+#             */
/*   Updated: 2022/03/31 15:28:05 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convchr(const char *s, t_data *data)
{
	size_t	i;

	i = 0;
	while ((s + data->pos)[i])
	{
		if ((s + data->pos)[i] == '%')
		{
			data->pos += i + 1;
			return (1);
		}
		i++;
	}
	return (0);
}
