/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:20:45 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/19 15:24:23 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_putfloat_prelim(t_data *data, long long nb)
{
	data->size = ((nb == 0) ? 1 : 0);
	while (nb != 0)
	{
		data->size++;
		nb = nb / 10;
	}
}

static void		ft_putfloat_ext_three(t_data *data, long long nb, \
		long double db)
{
	int prec;

	(db >= 0) ? ft_putlong(nb + 1, data) : ft_putlong(nb - 1, data);
	if ((data->precision != 0 || (data->precision == 0 &&\
		data->sharp == 1)))
		ft_fill_buffer(data, ".", 1);
	prec = data->precision;
	while (prec-- > 0)
		ft_fill_buffer(data, "0", 1);
}

static void		ft_putfloat_second(t_data *data, long double db,\
		long long nb, long double offset)
{
	int			prec;
	long double	db2;

	ft_putfloat_prelim(data, nb);
	db2 = (db >= 0) ? (db - (long long)db) * 10 : ((long long)db - db) * 10;
	nb = (long long)(data->precision == 0 ? db + offset : db);
	ft_set_padding_float(data, db);
	ft_putfloat_ext_one(data, db);
	prec = data->precision;
	while (prec >= 0 && ((long long)(db2) == 9 || (long long)(db2) % 10 == 9\
			|| (prec == 0 && (((long long)(db2) == 8 || \
			(long long)(db2) % 10 == 8) && ((long long)(db2 * 10) == 9 ||\
			(long long)(db2 * 10) % 10 == 9)))))
	{
		if (prec == 0)
		{
			nb = (long long)(data->precision == 0 ? db : db);
			ft_putfloat_ext_three(data, nb, db);
			prec = -1336;
		}
		db2 = (((long long)db2 == 9 || (long long)db2 % 10 == 9) ?\
				db2 * 10 : (db2 + 0.1) * 10);
		prec--;
	}
	ft_putfloat_ext_two(data, db, nb, prec);
}

static void		ft_putfloat_first(t_data *data, long double db)
{
	long double		offset;
	long long		nb;

	offset = ((db >= 0) ? 0.5000000000000000000000001 :\
			-0.5000000000000000000000001);
	nb = (long long)(data->precision == 0 ? db + offset : db);
	if (nb % 2 != 0)
	{
		offset = ((db >= 0) ? 0.49999999999999 :\
				-0.49999999999999);
		nb = (long long)(data->precision == 0 ? db + offset : db);
	}
	ft_putfloat_second(data, db, nb, offset);
}

void			ft_putfloat(t_data *data)
{
	long double	db;
	t_double	u;

	if (data->bits == 1)
	{
		db = va_arg(data->ap, double);
		u.value = db;
		ft_putbits_float(data, u.long_double_bits.sign,
			u.long_double_bits.power, u.long_double_bits.mantiss);
		return ;
	}
	db = ((data->length != 10) ? va_arg(data->ap, double) :\
			va_arg(data->ap, long double));
	u.value = db;
	if (db == 1.0 / 0.0 || db == -1.0 / 0.0 || db != db)
	{
		if (db == 1.0 / 0.0 || db == -1.0 / 0.0)
			((db >= 0) ? ft_fill_buffer(data, "inf", 3) :\
				ft_fill_buffer(data, "-inf", 4));
		else
			ft_fill_buffer(data, "nan", 3);
		return ;
	}
	ft_putfloat_first(data, db);
}
