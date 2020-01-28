/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:45:24 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/23 10:42:25 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_putlong_extend(t_data *data)
{
	data->res--;
	ft_fill_buffer(data, " ", 1);
}

void				ft_putlong(long long nb, t_data *data)
{
	char c;

	if (nb == 0)
	{
		ft_fill_buffer(data, "0", 1);
		return ;
	}
	if (nb > 0)
		nb = -nb;
	if (nb > -10)
	{
		c = '0' - nb;
		ft_fill_buffer(data, &c, 1);
		if (data->apos == 1 && data->space == 0 && data->precision == -1 && \
			data->sharp == 0 & (data->size + data->sign - data->res) % 3 == 0\
			&& (data->size + data->sign + data->sharp) != data->res)
			ft_putlong_extend(data);
	}
	else
	{
		ft_putlong(nb / 10, data);
		ft_putlong(nb % 10, data);
	}
}

static long long	ft_castints(t_data *data)
{
	long long nb;

	nb = va_arg(data->ap, long long);
	if (data->length == 1)
		nb = (char)nb;
	else if (data->length == 2)
		nb = (short)nb;
	else if (data->length == 4)
		nb = (int)nb;
	else if (data->length == 8)
		nb = (long)nb;
	else if (data->length == -8)
		nb = (long long)nb;
	if (nb < 0)
		data->space = 0;
	data->zero = ((data->zero == 1 && data->precision < 0) ? 1 : 0);
	data->sharp = 0;
	return (nb);
}

static void			ft_putnbr_ext_one(t_data *data, long long nb)
{
	ft_set_padding(data, nb);
	if (data->zero == 1)
		ft_put_sign(data, nb);
	ft_put_space(data, nb);
	ft_put_left_spaces(data);
	if (data->zero == 0)
		ft_put_sign(data, nb);
	ft_put_zeros(data);
	if (!(nb == 0 && data->precision == 0))
		ft_putlong(nb, data);
	ft_put_right_spaces(data);
}

void				ft_putnbr_printf(t_data *data)
{
	long long nb;
	long long nb2;

	nb = ft_castints(data);
	if (data->bits == 1)
	{
		ft_putbits_ints(data, nb);
		return ;
	}
	nb2 = nb;
	data->size = 0;
	if (nb2 == 0)
		data->size = ((data->precision != 0) ? 1 : 0);
	while (nb2 != 0)
	{
		data->size++;
		nb2 = nb2 / 10;
	}
	ft_putnbr_ext_one(data, nb);
}
