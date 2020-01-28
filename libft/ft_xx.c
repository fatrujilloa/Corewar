/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:45:24 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/17 11:20:20 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long	ft_castints_x(t_data *data)
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

static void					ft_putnbr_x_ext(t_data *data,
		unsigned long long nb)
{
	if (data->sharp == 1)
		data->sharp = (nb != 0) ? 2 : 0;
	ft_set_padding_u(data);
	if (nb != 0 && data->sharp == 2 && data->zero == 1)
		ft_fill_buffer(data, "0x", 2);
	ft_put_left_spaces(data);
	if (nb != 0 && data->sharp == 2 && data->zero == 0)
		ft_fill_buffer(data, "0x", 2);
	ft_put_zeros(data);
	ft_putlong_x(nb, data);
	ft_put_right_spaces(data);
}

void						ft_putnbr_x(t_data *data)
{
	unsigned long long nb;
	unsigned long long nb2;

	nb = ft_castints_x(data);
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
		nb2 = nb2 / 16;
	}
	ft_putnbr_x_ext(data, nb);
}

static void					ft_putnbr_xx_ext(t_data *data,
		unsigned long long nb)
{
	if (data->sharp == 1)
		data->sharp = (nb != 0) ? 2 : 0;
	ft_set_padding_u(data);
	if (nb != 0 && data->sharp == 2 && data->zero == 1)
		ft_fill_buffer(data, "0X", 2);
	ft_put_left_spaces(data);
	if (nb != 0 && data->sharp == 2 && data->zero == 0)
		ft_fill_buffer(data, "0X", 2);
	ft_put_zeros(data);
	if (!(nb == 0 && data->precision == 0))
		ft_putlong_xx(nb, data);
	ft_put_right_spaces(data);
}

void						ft_putnbr_xx(t_data *data)
{
	unsigned long long nb;
	unsigned long long nb2;

	nb = ft_castints_x(data);
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
		nb2 = nb2 / 16;
	}
	ft_putnbr_xx_ext(data, nb);
}
