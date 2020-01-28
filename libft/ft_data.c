/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:24:44 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/17 15:13:42 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_init_data(t_data *data, int fd)
{
	int i;

	i = 0;
	while (i < BUFF_SIZE)
		(data->buffer)[i++] = '\0';
	data->res = 0;
	data->i = 0;
	data->option = 0;
	data->sharp = 0;
	data->zero = 0;
	data->minus = 0;
	data->space = 0;
	data->plus = 0;
	data->fieldwidth = 0;
	data->precision = -1;
	data->length = 4;
	data->left_spaces = 0;
	data->sign = 0;
	data->zeros = 0;
	data->size = 0;
	data->right_spaces = 0;
	data->apos = 0;
	data->bits = 0;
	data->fd = fd;
}

void	ft_reset_data_options(t_data *data)
{
	data->option = 0;
	data->sharp = 0;
	data->zero = 0;
	data->minus = 0;
	data->space = 0;
	data->plus = 0;
	data->fieldwidth = 0;
	data->precision = -1;
	data->length = 4;
	data->left_spaces = 0;
	data->sign = 0;
	data->zeros = 0;
	data->size = 0;
	data->right_spaces = 0;
	data->apos = 0;
	data->bits = 0;
}
