/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:45:24 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/16 13:27:21 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void									ft_puttab(t_data *data)
{
	long long			*tab;
	unsigned long long	i;
	unsigned long long	size;

	i = 0;
	tab = va_arg(data->ap, long long *);
	size = va_arg(data->ap, unsigned long long);
	while (i < size)
	{
		if (tab[i] < 0)
			ft_fill_buffer(data, "-", 1);
		ft_putlong(tab[i], data);
		if (i != size - 1)
			ft_fill_buffer(data, " | ", 3);
		i++;
	}
}
