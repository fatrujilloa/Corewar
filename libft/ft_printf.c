/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 13:27:20 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/10/29 14:59:15 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_fill_buffer(t_data *data, const char *str, unsigned int size)
{
	unsigned int i;

	i = 0;
	if (data->res != -1)
		data->res = data->res + size;
	if (data->i + size > 2147483647)
		data->res = -1;
	if (data->i + size > BUFF_SIZE)
	{
		write(data->fd, data->buffer, data->i);
		data->i = 0;
	}
	if (size < BUFF_SIZE)
	{
		while (i < size)
		{
			(data->buffer)[data->i] = str[i];
			(data->i)++;
			i++;
		}
	}
	else
		write(data->fd, str, size);
}

static void	(*const g_ft_functions[128])(t_data *data) =
{
	['s'] = &ft_putstr_printf,
	['S'] = &ft_putstr_printf,
	['c'] = &ft_putchar_printf,
	['C'] = &ft_putchar_printf,
	['d'] = &ft_putnbr_printf,
	['D'] = &ft_putnbr_printf,
	['i'] = &ft_putnbr_printf,
	['u'] = &ft_putnbr_u,
	['U'] = &ft_putnbr_u,
	['o'] = &ft_putnbr_o,
	['O'] = &ft_putnbr_o,
	['x'] = &ft_putnbr_x,
	['X'] = &ft_putnbr_xx,
	['p'] = &ft_p,
	['%'] = &ft_percent,
	['f'] = &ft_putfloat,
	['T'] = &ft_puttab,
};

static void	ft_set_some_zeros(t_data *data)
{
	data->space = 0;
	data->plus = 0;
}

static void	ft_scan_format(const char *restrict format, t_data *data)
{
	int		i;
	char	c;
	int		len;

	len = ft_strlen(format);
	i = 0;
	while (i < len)
	{
		if (format[i] == '%')
		{
			i++;
			c = ft_parse_flags(format, data, &i);
			if (c == 'u' && (data->space == 1 || data->plus == 1))
				ft_set_some_zeros(data);
			if (c == 'D' || c == 'O' || c == 'U' || c == 'C' || c == 'S')
				data->length = 8;
			if (c)
				g_ft_functions[(int)c](data);
		}
		else if (format[i] == '{')
			ft_parse_colour(data, format, &i);
		else if (format[i] && format[i] != '%')
			ft_fill_buffer(data, format + i++, 1);
		ft_reset_data_options(data);
	}
}

int			ft_printf(const char *restrict format, ...)
{
	t_data	data;

	if (!(format))
		return (-1);
	ft_init_data(&data, 1);
	va_start(data.ap, format);
	ft_scan_format(format, &data);
	write(data.fd, data.buffer, data.i);
	va_end(data.ap);
	return (data.res);
}
