/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_to_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:31:08 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/17 15:14:59 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_attrib(const char *restrict str, int *i, t_data *data)
{
	while (str[*i] == '#' || str[*i] == '0' || str[*i] == '-' ||
			str[*i] == ' ' || str[*i] == '+' || str[*i] == 39 || str[*i] == 'B')
	{
		if (str[*i] == '#')
			data->sharp = 1;
		if (str[*i] == '0' && data->minus == 0)
			data->zero = 1;
		if (str[*i] == '-')
		{
			data->minus = 1;
			data->zero = 0;
		}
		if (str[*i] == ' ' && data->plus == 0)
			data->space = 1;
		if (str[*i] == '+')
		{
			data->plus = 1;
			data->space = 0;
		}
		if (str[*i] == 39)
			data->apos = 1;
		if (str[*i] == 'B')
			data->bits = 1;
		(*i)++;
	}
}

void	ft_fieldwidth(const char *restrict str, int *i, t_data *data)
{
	int		nb;

	if ((str[*i] >= '1' && str[*i] <= '9'))
	{
		nb = ft_atoi(str + *i);
		data->fieldwidth = nb;
		while ((str[*i] >= '0' && str[*i] <= '9'))
			(*i)++;
	}
	else if (str[*i] == '*')
	{
		data->fieldwidth = va_arg(data->ap, int);
		if (data->fieldwidth < 0)
		{
			data->fieldwidth = -data->fieldwidth;
			data->minus = 1;
		}
		(*i)++;
	}
}

void	ft_precision(const char *restrict str, int *i, t_data *data)
{
	int nb;

	while (str[*i] == '.')
		(*i)++;
	if (str[*i] >= '0' && str[*i] <= '9')
	{
		nb = ft_atoi(str + *i);
		data->precision = nb;
		while (str[*i] >= '0' && str[*i] <= '9')
			(*i)++;
	}
	else if (str[*i] == '*')
	{
		data->precision = va_arg(data->ap, int);
		if (data->precision < 0)
			data->precision = -1;
		(*i)++;
	}
	else
		data->precision = 0;
}

void	ft_lengthmod(const char *restrict str, int *i, t_data *data)
{
	int l;
	int h;
	int ll;

	l = 0;
	h = 0;
	ll = 0;
	while ((str[*i] == 'h' || str[*i] == 'l' || str[*i] == 'L'))
	{
		l = l + (str[*i] == 'l' ? 1 : 0);
		h = h + (str[*i] == 'h' ? 1 : 0);
		ll = ll + (str[(*i)++] == 'L' ? 1 : 0);
	}
	if (l == 1)
		data->length = 8;
	else if (h == 2)
		data->length = 1;
	else if (h == 1)
		data->length = 2;
	else if (l >= 2)
		data->length = -8;
	else if (ll >= 1)
		data->length = 10;
	else
		data->length = 4;
}
