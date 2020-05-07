/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 18:26:40 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/07 02:41:13 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	ft_strswap(char *a, char *b, unsigned int size)
{
	char *t;

	t = (char*)malloc(size + 1);
	ft_memcpy(t, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, t, size);
	free(t);
}

int		ft_display_options(void)
{
	ft_printf("{RED}./corewar{EOC} {YELLOW}[-dump nbr_cycles] {EOC}");
	ft_printf("{GREEN}[{EOC}{YELLOW}[-n number]{EOC}");
	ft_printf("{GREEN} champion1.cor]{EOC} ...\n");
	return (1);
}
