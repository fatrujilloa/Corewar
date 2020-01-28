/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 19:21:25 by rbeaufre          #+#    #+#             */
/*   Updated: 2020/01/05 17:12:04 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int	ft_display_options(void)
{
	ft_printf("{RED}./corewar{EOC} {YELLOW}[-dump nbr_cycles] {EOC}");
	ft_printf("{GREEN}[{EOC}{YELLOW}[-n number]{EOC}");
	ft_printf("{GREEN} champion1.cor]{EOC} ...\n");
	return (1);
}
