/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_colour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:14:06 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/10/28 19:19:00 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_put_colors_two(t_data *data, const char *s, int *i)
{
	if (ft_strnequ(s + *i, "{CYAN}", 6))
	{
		ft_fill_buffer(data, CYAN, 7);
		(*i) += 6;
	}
	else if (ft_strnequ(s + *i, "{YELLOW}", 8))
	{
		ft_fill_buffer(data, YELLOW, 7);
		(*i) += 8;
	}
	else if (ft_strnequ(s + *i, "{MAGENTA}", 9))
	{
		ft_fill_buffer(data, MAGENTA, 7);
		(*i) += 9;
	}
}

static void		ft_put_colors(t_data *data, const char *s, int *i)
{
	if (ft_strnequ(s + *i, "{RED}", 5))
	{
		ft_fill_buffer(data, RED, 7);
		(*i) += 5;
	}
	else if (ft_strnequ(s + *i, "{EOC}", 5))
	{
		ft_fill_buffer(data, EOC, 7);
		(*i) += 4;
	}
	else if (ft_strnequ(s + *i, "{GREEN}", 7))
	{
		ft_fill_buffer(data, GREEN, 7);
		(*i) += 7;
	}
	else if (ft_strnequ(s + *i, "{BLUE}", 6))
	{
		ft_fill_buffer(data, BLUE, 7);
		(*i) += 6;
	}
	else
		ft_put_colors_two(data, s, i);
}

void			ft_parse_colour(t_data *data, const char *format, int *i)
{
	if (ft_strnequ(format + *i, "{RED}", 5) == 1
		|| ft_strnequ(format + *i, "{EOC}", 5) == 1
		|| ft_strnequ(format + *i, "{GREEN}", 7) == 1
		|| ft_strnequ(format + *i, "{BLUE}", 6) == 1
		|| ft_strnequ(format + *i, "{CYAN}", 6) == 1
		|| ft_strnequ(format + *i, "{YELLOW}", 8) == 1
		|| ft_strnequ(format + *i, "{MAGENTA}", 9) == 1)
	{
		ft_put_colors(data, format, i);
	}
	else
	{
		ft_fill_buffer(data, format + (*i)++, 1);
	}
}
