/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:48:24 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/19 15:18:26 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long	ft_pow(int length)
{
	int					i;
	unsigned long long	res;

	i = 0;
	res = 1;
	while (i < length - 1)
	{
		res = res * 2;
		i++;
	}
	return (res);
}

void						ft_putbits_u(t_data *data, unsigned long long nb)
{
	unsigned long long			i;
	unsigned long long			c;
	int							count;

	count = 1;
	if (data->length == -8 || data->length == 10)
		data->length = 8;
	i = ft_pow(data->length * 8);
	c = nb;
	while (i)
	{
		(c & i) ? ft_fill_buffer(data, "1", 1) : ft_fill_buffer(data, "0", 1);
		if (count % 4 == 0)
			ft_fill_buffer(data, " ", 1);
		if (count % 8 == 0 && i != 1)
			ft_fill_buffer(data, "-", 1);
		if (i != 1)
			ft_fill_buffer(data, " ", 1);
		i = i >> 1;
		count++;
	}
}

void						ft_putbits_ints(t_data *data, long long nb)
{
	unsigned long long			i;
	long long					c;
	int							count;

	count = 1;
	if (data->length == -8 || data->length == 10)
		data->length = 8;
	i = ft_pow(data->length * 8);
	c = nb;
	while (i)
	{
		(c & i) ? ft_fill_buffer(data, "1", 1) : ft_fill_buffer(data, "0", 1);
		if (count % 4 == 0 && i != 1)
			ft_fill_buffer(data, " ", 1);
		if (count % 8 == 0 && i != 1)
			ft_fill_buffer(data, "-", 1);
		if (i != 1)
			ft_fill_buffer(data, " ", 1);
		i = i >> 1;
		count++;
	}
}

static void					ft_putbits_float_print(t_data *data,
		unsigned long long c, unsigned long long i, int count)
{
	while (i)
	{
		(c & i) ? ft_fill_buffer(data, "1", 1) : ft_fill_buffer(data, "0", 1);
		if (count % 4 == 0 && i != 1)
			ft_fill_buffer(data, " ", 1);
		if (count % 8 == 0 && i != 1)
			ft_fill_buffer(data, "-", 1);
		if (i != 1)
			ft_fill_buffer(data, " ", 1);
		i = i >> 1;
		count++;
	}
}

void						ft_putbits_float(t_data *data,
	unsigned long long sign, unsigned long long power,
	unsigned long long mantiss)
{
	unsigned long long			i;
	unsigned long long			c;

	c = sign;
	i = 1;
	(c & i) ? ft_fill_buffer(data, "1", 1) : ft_fill_buffer(data, "0", 1);
	(void)(mantiss);
	(void)(power);
	ft_fill_buffer(data, " / ", 3);
	i = 16384;
	c = power;
	ft_putbits_float_print(data, c, i, 2);
	ft_fill_buffer(data, " / ", 3);
	c = mantiss;
	i = 9223372036854775808llu;
	ft_putbits_float_print(data, c, i, 1);
}
