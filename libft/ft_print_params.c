/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 20:48:46 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/07 14:56:43 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_print_params(int argc, char **argv)
{
	int i;

	(void)argc;
	i = 1;
	while (argv[i])
	{
		ft_putstr(argv[i++]);
		ft_putchar('\n');
	}
	return (0);
}
