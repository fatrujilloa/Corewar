/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:20:45 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/14 17:21:30 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_put_extra_zeros(t_data *data, int prec)
{
	while (prec > 1)
	{
		ft_fill_buffer(data, "0", 1);
		prec--;
	}
}

void		ft_putfloat_ext_one(t_data *data, long double db)
{
	if (data->zero == 1)
		ft_put_sign_float(data, db);
	ft_put_space_float(data, db);
	ft_put_left_spaces_whole_float(data);
	if (data->zero == 0)
		ft_put_sign_float(data, db);
}

void		ft_putfloat_ext_two(t_data *data, long double db,\
		long long nb, int prec)
{
	if (prec != -1337)
		ft_putlong(nb, data);
	if ((data->precision != 0 || (data->precision == 0 &&\
			data->sharp == 1)) && prec != -1337)
		ft_prec_zero(data, db);
	ft_put_right_spaces(data);
}

void		ft_prec_zero(t_data *data, long double db)
{
	ft_fill_buffer(data, ".", 1);
	if (data->precision != 0)
		ft_put_dec(data, db);
}

void		ft_put_dec(t_data *data, long double db)
{
	int					prec;
	long double			db2;
	long double			db3;
	unsigned long long	mult;
	long double			offset;

	offset = ((db >= 0) ? 0.4999999999999999999999999 :\
			-0.4999999999999999999999999);
	mult = 1;
	db2 = db - (long long)db;
	prec = (int)data->precision;
	while ((long long)(db2 * 10 + (offset / 10)) == 0 && prec > 0)
	{
		ft_fill_buffer(data, "0", 1);
		db2 = db2 * 10;
		if (prec == 1)
			return ;
		prec--;
	}
	while (prec-- > 0)
		mult = mult * 10;
	db3 = (db2 * mult);
	if ((long long)db3 == 0 && prec >= 0)
		ft_put_extra_zeros(data, prec);
	ft_putlong((long long)(db3 + offset), data);
}
