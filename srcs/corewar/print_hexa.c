/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 18:28:36 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/06 18:28:58 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int		ft_is_line_empty(char *str, int i, int size, int *flag)
{
	int j;

	j = 0;
	while (j < 16 && i + j < size)
	{
		if ((unsigned char)(str[i + j] % 16) != 0
			|| (unsigned char)((str[i] / 16) % 16) != 0)
			return (0);
		j++;
	}
	*flag = 0;
	return (1);
}

int				ft_print_hexa(char *str, int size)
{
	int	i;
	int	mod;
	int	flag;

	flag = 1;
	i = 0;
	mod = 16;
	ft_printf("Ox0000 : ");
	while (i < size)
	{
		if (i % mod == 0 && i != 0)
		{
			flag = 1;
			if (ft_is_line_empty(str, i, size, &flag) == 1)
				i = i * 1;
			else
				ft_printf("\n0x0%03x : ", i);
		}
		if (flag == 1)
			ft_printf("%02x ", (unsigned char)str[i]);
		i++;
	}
	ft_printf("\n");
	return (1);
}
