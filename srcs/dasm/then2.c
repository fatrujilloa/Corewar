/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   then.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:36:07 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 17:50:13 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

t_op_n			change_op_n(int i, int j, int opcode)
{
	t_op_n	n;

	n.i = i;
	n.j = j;
	n.opcode = opcode;
	return (n);
}

unsigned long	puissance(unsigned long nb, int p)
{
	unsigned long	nb_f;

	nb_f = nb;
	if (p == 0)
		return (1);
	while (p > 1)
	{
		nb_f = nb_f * nb;
		p--;
	}
	return (nb_f);
}

int				write_opcode(t_dasm *dasm, int opcode, t_op *op_tab)
{
	int		i;

	i = 0;
	while (op_tab[opcode - 1].name[i])
	{
		dasm->tab[dasm->nb_tab][i] = op_tab[opcode - 1].name[i];
		i++;
	}
	dasm->tab[dasm->nb_tab][i] = ' ';
	return (i + 1);
}

t_op_n			write_big_a_1(t_op_n n, int pass, t_dasm *dasm, t_op *op_tab)
{
	if (op_tab[n.opcode - 1].args[pass] != T_REG
			&& op_tab[n.opcode - 1].args[pass] != T_REG + T_DIR
			&& op_tab[n.opcode - 1].args[pass] != T_REG + T_IND
			&& op_tab[n.opcode - 1].args[pass] != T_REG + T_IND + T_DIR)
	{
		n.i = -1;
		return (n);
	}
	n.j = write_reg(dasm, n.j, n.i);
	n.i = n.i + 1;
	return (n);
}

t_op_n			write_big_a_2(t_op_n n, int pass, t_dasm *dasm, t_op *op_tab)
{
	if (op_tab[n.opcode - 1].args[pass] != T_DIR
			&& op_tab[n.opcode - 1].args[pass] != T_DIR + T_REG
			&& op_tab[n.opcode - 1].args[pass] != T_DIR + T_IND
			&& op_tab[n.opcode - 1].args[pass] != T_DIR + T_REG + T_IND)
	{
		n.i = -1;
		return (n);
	}
	dasm->i = n.i;
	n.j = write_dir(dasm, n.j, n.opcode, op_tab);
	if (op_tab[n.opcode - 1].label == 1)
		n.i = n.i + 2;
	else
		n.i = n.i + 4;
	return (n);
}
