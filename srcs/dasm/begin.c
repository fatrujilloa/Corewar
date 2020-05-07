/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:30:36 by gmoindro          #+#    #+#             */
/*   Updated: 2020/01/30 12:31:17 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

int		check_magic_number(t_dasm *dasm)
{
	int	magic_number;

	magic_number = dasm->buf[0] * 16777216;
	magic_number = magic_number + dasm->buf[1] * 65536;
	magic_number = magic_number + dasm->buf[2] * 256;
	magic_number = magic_number + dasm->buf[3];
	if (magic_number == COREWAR_EXEC_MAGIC)
		return (1);
	return (-1);
}

void	put_name_in_tab(t_dasm *dasm)
{
	int	i;

	i = 4;
	while (i < (4 + PROG_NAME_LENGTH))
	{
		dasm->tab[0][i - 4] = dasm->buf[i];
		i++;
	}
}

int		check_padding(t_dasm *dasm, int place)
{
	int	nb;

	nb = dasm->buf[place] + dasm->buf[place + 1]
		+ dasm->buf[place + 2] + dasm->buf[place + 3];
	if (nb == 0)
		return (1);
	return (-1);
}

void	put_comment_in_tab(t_dasm *dasm)
{
	int	i;

	i = 12 + PROG_NAME_LENGTH;
	while (i < (12 + PROG_NAME_LENGTH + COMMENT_LENGTH))
	{
		dasm->tab[1][i - 12 - PROG_NAME_LENGTH] = dasm->buf[i];
		i++;
	}
}

int		check_number_instruct(t_dasm *dasm)
{
	int	nb_inst;

	nb_inst = dasm->buf[8 + PROG_NAME_LENGTH] * 16777216;
	nb_inst = nb_inst + dasm->buf[9 + PROG_NAME_LENGTH] * 65536;
	nb_inst = nb_inst + dasm->buf[10 + PROG_NAME_LENGTH] * 256;
	nb_inst = nb_inst + dasm->buf[11 + PROG_NAME_LENGTH];
	if (nb_inst == dasm->ret - PROG_NAME_LENGTH - COMMENT_LENGTH - 16)
		return (1);
	return (-1);
}
