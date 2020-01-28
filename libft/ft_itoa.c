/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:06:56 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/11 10:25:14 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(int n)
{
	int size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static void	ft_fill_res(int size, int offset, int n, char *res)
{
	while (size > offset)
	{
		res[size - 1] = n % 10 + '0';
		n = n / 10;
		size--;
	}
}

char		*ft_itoa(int n)
{
	int		offset;
	int		size;
	char	*res;

	offset = 0;
	size = ft_get_size(n);
	if (!(res = (char *)malloc(sizeof(char) * size + 1)))
		return (0);
	if (n == -2147483648)
	{
		res[0] = '-';
		res[1] = '2';
		n = 147483648;
		offset = 2;
	}
	if (n < 0)
	{
		res[0] = '-';
		offset = 1;
		n = -n;
	}
	ft_fill_res(size, offset, n, res);
	res[size] = '\0';
	return (res);
}
