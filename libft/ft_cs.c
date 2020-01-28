/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:49:18 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/23 10:37:48 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_printf(t_data *data)
{
	char c;

	c = (unsigned char)va_arg(data->ap, int);
	if (data->bits == 1)
	{
		ft_putbits_u(data, c);
		return ;
	}
	if (c >= 0 && c <= 127)
		data->size = 1;
	if (data->minus == 1)
		data->right_spaces = data->fieldwidth - data->sign \
		- data->zeros - data->size - data->sharp;
	else
		data->left_spaces = data->fieldwidth - data->sign \
		- data->zeros - data->size - data->sharp;
	ft_put_left_spaces(data);
	ft_fill_buffer(data, &c, 1);
	ft_put_right_spaces(data);
}

void	ft_putstr_printf(t_data *data)
{
	char	*str;
	int		len;

	str = va_arg(data->ap, char *);
	if (str == NULL)
		str = "(null)";
	len = (int)ft_strlen(str);
	if (str && (data->precision == -1 || data->precision >= len))
		data->size = len;
	else if (str && data->precision < len)
	{
		data->size = data->precision;
		len = data->precision;
	}
	if (data->minus == 1)
		data->right_spaces = data->fieldwidth - data->sign \
		- data->zeros - data->size - data->sharp;
	else
		data->left_spaces = data->fieldwidth - data->sign - \
		data->zeros - data->size - data->sharp;
	ft_put_left_spaces(data);
	ft_fill_buffer(data, str, len);
	ft_put_right_spaces(data);
}
