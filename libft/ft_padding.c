/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 19:17:39 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/15 13:03:01 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_set_padding(t_data *data, long long nb)
{
	data->sign = ((nb < 0 || data->plus == 1) ? 1 : 0);
	if (data->precision != -1)
		data->zeros = data->precision - data->size;
	if (data->zeros < 0)
		data->zeros = 0;
	data->left_spaces = 0;
	data->right_spaces = 0;
	if (data->minus == 1)
	{
		data->right_spaces = data->fieldwidth - data->sign \
		- data->zeros - data->size - data->sharp - data->space;
	}
	else
	{
		data->left_spaces = data->fieldwidth - data->sign \
		- data->zeros - data->size - data->sharp - data->space;
	}
}

void	ft_put_left_spaces(t_data *data)
{
	while (data->left_spaces > 0)
	{
		if (data->zero == 1 && (data->precision <= 0))
			ft_fill_buffer(data, "0", 1);
		else
			ft_fill_buffer(data, " ", 1);
		data->left_spaces--;
	}
}

void	ft_put_right_spaces(t_data *data)
{
	while (data->right_spaces > 0)
	{
		ft_fill_buffer(data, " ", 1);
		data->right_spaces--;
	}
}

void	ft_put_zeros(t_data *data)
{
	while (data->zeros > 0)
	{
		ft_fill_buffer(data, "0", 1);
		data->zeros--;
	}
}

void	ft_put_sign(t_data *data, long long nb)
{
	if (data->sign == 1)
	{
		if (nb < 0)
			ft_fill_buffer(data, "-", 1);
		else if (nb >= 0 && data->plus == 1)
			ft_fill_buffer(data, "+", 1);
	}
}
