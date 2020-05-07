/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_turn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:50:26 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 16:45:48 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int			check_name_c(char *line, int *quote, int *len_name)
{
	int		r;

	if ((r = ft_len_next(line, quote)) < 0)
		return (return_f("FATAL ERROR - wrong syntax name\n", -1));
	*len_name = *len_name + r;
	if (*quote == 1)
		*len_name = *len_name + 1;
	else if (*quote == 2)
		return (*len_name);
	return (1);
}

int			check_name_b(char *line, int *name, int *quote, int *len_name)
{
	char	*str;

	if (*name == 0 && (str = ft_strstr(line, NAME_CMD_STRING)))
	{
		*name = *name + 1;
		if (check_nothing_before(line, NAME_CMD_STRING, 0) == 0)
			return (return_f("FATAL ERROR - wrong syntax name\n", -1));
		if ((*len_name = ft_len_begin(str, NAME_CMD_STRING, quote)) < 0)
			return (return_f("FATAL ERROR - wrong syntax name\n", -1));
		if (*quote == 1)
			*len_name = *len_name + 1;
		if (*quote == 2)
			return (*len_name);
	}
	else if (*name == 0 && ft_strstr(line, NAME_CMD_STRING) == NULL)
	{
		if (check_nothing(line) == 0)
			return (return_f("FATAL_ERROR - wrong syntax on a line\n", -1));
	}
	else
		return (check_name_c(line, quote, len_name));
	return (1);
}
