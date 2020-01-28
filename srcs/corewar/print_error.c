/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:35:03 by rbeaufre          #+#    #+#             */
/*   Updated: 2020/01/12 12:39:39 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int	ft_print_error(char *str)
{
	char c;

	c = '\n';
	write(2, "Error output: ", 14);
	write(2, str, ft_strlen(str));
	write(2, &c, 1);
	return (1);
}
