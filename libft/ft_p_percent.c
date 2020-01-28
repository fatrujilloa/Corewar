/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 14:29:18 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/12 18:24:53 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_percent(t_data *data)
{
	data->size = 1;
	if (data->minus == 1)
		data->right_spaces = data->fieldwidth - data->sign \
		- data->zeros - data->size - data->sharp;
	else
		data->left_spaces = data->fieldwidth - data->sign \
		- data->zeros - data->size - data->sharp;
	ft_put_left_spaces(data);
	ft_fill_buffer(data, "%", 1);
	ft_put_right_spaces(data);
}

void	ft_p(t_data *data)
{
	long nb;
	long nb2;

	nb = va_arg(data->ap, unsigned long);
	data->plus = 0;
	nb2 = nb;
	data->size = 0;
	if (nb2 == 0 && data->precision != 0)
		(data->size = 1);
	while (nb2 != 0)
	{
		(data->size)++;
		nb2 = nb2 / 16;
	}
	data->sharp = 2;
	ft_set_padding(data, nb);
	if (data->sharp == 2 && data->zero == 1)
		ft_fill_buffer(data, "0x", 2);
	ft_put_left_spaces(data);
	if (data->sharp == 2 && data->zero != 1)
		ft_fill_buffer(data, "0x", 2);
	ft_put_sign(data, nb);
	ft_put_zeros(data);
	ft_putlong_x(nb, data);
	ft_put_right_spaces(data);
}
