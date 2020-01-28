/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xx_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:45:24 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/17 11:19:11 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					ft_putlong_x(unsigned long long nb, t_data *data)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb == 0)
	{
		if (data->precision != 0)
			ft_fill_buffer(data, "0", 1);
		return ;
	}
	if (nb < 16)
		ft_fill_buffer(data, base + nb, 1);
	else
	{
		ft_putlong_x(nb / 16, data);
		ft_putlong_x(nb % 16, data);
	}
}

void					ft_putlong_xx(unsigned long long nb, t_data *data)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (nb == 0)
	{
		if (data->precision != 0)
			ft_fill_buffer(data, "0", 1);
		return ;
	}
	if (nb < 16)
		ft_fill_buffer(data, base + nb, 1);
	else
	{
		ft_putlong_xx(nb / 16, data);
		ft_putlong_xx(nb % 16, data);
	}
}
