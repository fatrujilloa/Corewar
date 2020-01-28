/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding_float2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 19:17:39 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/16 13:27:31 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_left_spaces_float(t_data *data)
{
	while (data->left_spaces > 0)
	{
		if (data->zero == 1 && (data->precision == -1 || data->precision == 0))
			ft_fill_buffer(data, "0", 1);
		else
			ft_fill_buffer(data, " ", 1);
		data->left_spaces--;
	}
}

void	ft_put_right_spaces_float(t_data *data)
{
	while (data->right_spaces > 0)
	{
		ft_fill_buffer(data, " ", 1);
		data->right_spaces--;
	}
}

void	ft_put_left_spaces_whole_float(t_data *data)
{
	while (data->left_spaces > 0)
	{
		if (data->zero == 1 && (data->precision <= 6))
			ft_fill_buffer(data, "0", 1);
		else
			ft_fill_buffer(data, " ", 1);
		data->left_spaces--;
	}
}
