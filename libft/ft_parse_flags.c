/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 13:41:41 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/17 15:12:18 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		ft_converter(const char *restrict str, int *i, t_data *data)
{
	if (!(str[*i] == 'd' || str[*i] == 'i' || str[*i] == 'o' \
		|| str[*i] == 'u' || str[*i] == 'x' || str[*i] == 'X' \
		|| str[*i] == 'f' || str[*i] == 'c' || str[*i] == 's' \
		|| str[*i] == 'p' || str[*i] == '%' || str[*i] == 'D' \
		|| str[*i] == 'O' || str[*i] == 'U' || str[*i] == 'C' \
		|| str[*i] == 'T'))
	{
		data->converterror = str + *i;
		if (str[*i] == '\0')
			return (0);
		(*i)++;
		return (0);
	}
	(*i)++;
	return (str[*i - 1]);
}

char			ft_parse_flags(const char *restrict str, t_data *data, int *i)
{
	while (str[*i] == '#' || str[*i] == '0' || str[*i] == '-' \
			|| str[*i] == ' ' || str[*i] == '+' \
			|| (str[*i] >= '1' && str[*i] <= '9') || str[*i] == '.' \
			|| str[*i] == 'h' || str[*i] == 'l' || str[*i] == 'L' \
			|| str[*i] == '*' || str[*i] == 39 || str[*i] == 'B')
	{
		if (str[*i] == '#' || str[*i] == '0' || str[*i] == '-' || str[*i] == ' '
			|| str[*i] == '+' || str[*i] == 39 || str[*i] == 'B')
			ft_attrib(str, i, data);
		else if ((str[*i] >= '1' && str[*i] <= '9') || str[*i] == '*')
			ft_fieldwidth(str, i, data);
		else if (str[*i] == '.')
			ft_precision(str, i, data);
		else if (str[*i] == 'h' || str[*i] == 'l' || str[*i] == 'L')
			ft_lengthmod(str, i, data);
	}
	return (ft_converter(str, i, data));
}
