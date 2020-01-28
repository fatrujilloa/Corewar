/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 19:17:39 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/19 15:12:01 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void		ft_set_padding_float(t_data *data, long double db)
{
	int point;

	point = ((data->precision == 0 && data->sharp != 1 &&\
				data->fieldwidth != 0) ? 0 : 1);
	data->sign = (((db) < 0 || db == -0.0 || data->plus == 1) ? 1 : 0);
	if (db < 0.0)
		data->space = 0;
	data->left_spaces = 0;
	data->right_spaces = 0;
	data->precision = ((data->precision == -1) ? 6 : data->precision);
	if (data->minus == 1)
	{
		data->right_spaces = data->fieldwidth - data->space\
			- data->sign - data->size - point - data->precision;
	}
	else
	{
		data->left_spaces = data->fieldwidth - data->space\
			- data->sign - data->size - point - data->precision;
	}
}

void		ft_put_zeros_float(t_data *data)
{
	while (data->zeros > 0)
	{
		ft_fill_buffer(data, "0", 1);
		data->zeros--;
	}
}

void		ft_put_sign_float(t_data *data, long double db)
{
	t_double	u;

	u.value = db;
	if (data->sign == 1)
	{
		if (u.long_double_bits.sign == 1)
			ft_fill_buffer(data, "-", 1);
		else if (u.long_double_bits.sign == 0 && data->plus == 1)
			ft_fill_buffer(data, "+", 1);
	}
}

void		ft_put_space_float(t_data *data, long double db)
{
	if (data->space == 1 && data->plus != 1 && db >= 0.0)
		ft_fill_buffer(data, " ", 1);
}
