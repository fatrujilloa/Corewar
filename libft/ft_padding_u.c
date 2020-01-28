/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 19:17:39 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/14 16:51:30 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_set_padding_u(t_data *data)
{
	data->sign = ((data->plus == 1) ? 1 : 0);
	if (data->precision != -1)
		data->zeros = data->precision - data->size;
	if (data->zeros < 0)
		data->zeros = 0;
	data->left_spaces = 0;
	data->right_spaces = 0;
	if (data->minus == 1)
	{
		data->right_spaces = data->fieldwidth - data->space\
			- data->sign - data->sharp - data->zeros - data->size;
	}
	else
	{
		data->left_spaces = data->fieldwidth - data->space\
			- data->sign - data->sharp - data->zeros - data->size;
	}
}

void	ft_put_sign_u(t_data *data)
{
	if (data->sign == 1)
	{
		if (data->plus == 1)
			ft_fill_buffer(data, "+", 1);
	}
}

void	ft_put_space_u(t_data *data)
{
	if (data->space == 1 && data->plus != 1)
		ft_fill_buffer(data, " ", 1);
}
