/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:45:24 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/17 11:13:17 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void					ft_putlong_u(unsigned long long nb, t_data *data)
{
	char c;

	if (nb == 0)
	{
		ft_fill_buffer(data, "0", 1);
		return ;
	}
	if (nb < 10)
	{
		c = '0' + nb;
		ft_fill_buffer(data, &c, 1);
	}
	else
	{
		ft_putlong_u(nb / 10, data);
		ft_putlong_u(nb % 10, data);
	}
}

static unsigned long long	ft_castints_u(t_data *data)
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
	data->zero = ((data->zero == 1 && data->precision < 0) ? 1 : 0);
	return (nb);
}

static void					ft_putnbr_u_ext(t_data *data,
		unsigned long long nb)
{
	ft_set_padding_u(data);
	if (data->zero == 1)
		ft_put_sign_u(data);
	ft_put_left_spaces(data);
	if (data->zero == 0)
		ft_put_sign_u(data);
	ft_put_space_u(data);
	ft_put_zeros(data);
	if (!(nb == 0 && data->precision == 0))
		ft_putlong_u(nb, data);
	ft_put_right_spaces(data);
}

void						ft_putnbr_u(t_data *data)
{
	unsigned long long nb;
	unsigned long long nb2;

	nb = ft_castints_u(data);
	if (data->bits == 1)
	{
		ft_putbits_u(data, nb);
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
	ft_putnbr_u_ext(data, nb);
}
