/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_o.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:45:24 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/17 11:10:38 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long	ft_castints_o(t_data *data)
{
	unsigned long long nb;

	nb = va_arg(data->ap, unsigned long long);
	if (data->length == 1)
		nb = (unsigned char)nb;
	else if (data->length == 2)
		nb = (unsigned short)nb;
	else if (data->length == 4)
		nb = (unsigned int)nb;
	else if (data->length == 8)
		nb = (unsigned long)nb;
	else if (data->length == -8)
		nb = (unsigned long long)nb;
	data->plus = 0;
	data->zero = ((data->zero == 1 && data->precision < 0) ? 1 : 0);
	return (nb);
}

static void					ft_putlong_o(unsigned long long nb, t_data *data)
{
	char	*base;

	base = "01234567";
	if (nb == 0)
	{
		if (data->precision != 0)
			ft_fill_buffer(data, "0", 1);
		return ;
	}
	if (nb < 8)
		ft_fill_buffer(data, base + nb, 1);
	else
	{
		ft_putlong_o(nb / 8, data);
		ft_putlong_o(nb % 8, data);
	}
}

void						ft_putnbr_o_s(t_data *data, unsigned long long nb)
{
	if (data->sharp == 1 && nb == 0 && data->fieldwidth > 1 && \
		data->minus == 0 && data->zero != 1 && data->precision < -1)
		ft_fill_buffer(data, " ", 1);
	if (data->sharp == 1)
		(data->zero == 1 && nb == 0) ? ft_fill_buffer(data, "00", 2) :\
			ft_fill_buffer(data, "0", 1);
	ft_put_zeros(data);
	if ((!(data->sharp == 1 && nb == 0 && data->precision < 0)))
		ft_putlong_o(nb, data);
	if (data->sharp == 1 && nb == 0 && data->fieldwidth > 1 && \
		data->minus == 1 && data->zero != 1 && data->precision < -1)
		ft_fill_buffer(data, " ", 1);
	ft_put_right_spaces(data);
}

void						ft_putnbr_o(t_data *data)
{
	unsigned long long nb;
	unsigned long long nb2;

	nb = ft_castints_o(data);
	if (data->bits == 1)
	{
		ft_putbits_u(data, nb);
		return ;
	}
	nb2 = nb;
	data->size = 0;
	if (nb2 == 0 && data->precision != 0)
		(data->size = 1);
	while (nb2 != 0)
	{
		(data->size)++;
		nb2 = nb2 / 8;
	}
	if (data->sharp == 1)
		data->precision--;
	ft_set_padding_u(data);
	ft_put_left_spaces(data);
	ft_putnbr_o_s(data, nb);
}
