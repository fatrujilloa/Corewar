/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:40:28 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/11 10:59:36 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		ft_get_base(int b)
{
	char *base;

	base = "0123456789ABCDEF";
	return (base[b]);
}

static int		ft_get_size(int n, int base)
{
	int i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

static void		ft_fill_res(int offset, int n, char *res, int base)
{
	int size;

	size = ft_get_size(n, base);
	while (size > offset)
	{
		res[size - 1] = ft_get_base(n % base);
		n = n / base;
		size--;
	}
}

char			*ft_itoa_base(int n, int base)
{
	int		offset;
	int		size;
	char	*res;

	if (base < 2 || base > 16)
		return (NULL);
	if (n == -2147483648 && base == 10)
		return ("-2147483648");
	size = ft_get_size(n, base);
	res = NULL;
	if (!(res = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	offset = 0;
	if (n < 0)
	{
		res[0] = '-';
		offset = 1;
		n = -n;
	}
	ft_fill_res(offset, n, res, base);
	res[size] = '\0';
	return (res);
}
