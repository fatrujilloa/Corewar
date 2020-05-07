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

t_op_n			write_big_a_3(t_op_n n, int pass, t_dasm *dasm, t_op *op_tab)
{
	if (op_tab[n.opcode - 1].args[pass] != T_IND
			&& op_tab[n.opcode - 1].args[pass] != T_IND + T_REG
			&& op_tab[n.opcode - 1].args[pass] != T_IND + T_DIR
			&& op_tab[n.opcode - 1].args[pass] != T_IND + T_DIR + T_REG)
	{
		n.i = -1;
		return (n);
	}
	n.j = write_ind(dasm, n.j, n.i);
	n.i = n.i + 2;
	return (n);
}

int				write_big_arg(t_dasm *dasm, unsigned int nb_i,
					t_op_n n, t_op *op_tab)
{
	int		pass;
	int		inst;

	pass = 0;
	n.i = n.i + 2;
	while (nb_i > 0)
	{
		if (pass > 0)
			dasm->tab[dasm->nb_tab][n.j++] = SEPARATOR_CHAR;
		inst = nb_i / puissance(2, (6 - (pass * 2)));
		nb_i = nb_i - (inst * puissance(2, (6 - (pass * 2))));
		if (inst == 1)
			n = write_big_a_1(n, pass, dasm, op_tab);
		else if (inst == 3)
			n = write_big_a_3(n, pass, dasm, op_tab);
		else if (inst == 2)
			n = write_big_a_2(n, pass, dasm, op_tab);
		else
			return (-1);
		if (n.i < 0)
			return (-1);
		pass++;
	}
	return (n.i);
}

int				write_small_arg(t_dasm *dasm, t_op_n n, t_op *op_tab)
{
	if (op_tab[n.opcode - 1].args[0] == 1)
	{
		write_reg(dasm, n.j, n.i + 1);
		return (1);
	}
	else if (op_tab[n.opcode - 1].args[0] == 2)
	{
		dasm->i = n.i + 1;
		write_dir(dasm, n.j, n.opcode, op_tab);
		if (op_tab[n.opcode - 1].label == 1)
			return (2);
		return (4);
	}
	else if (op_tab[n.opcode - 1].args[0] == 3)
	{
		write_ind(dasm, n.j, n.i + 1);
		return (2);
	}
	return (-1);
}

int				instruct_alone(t_dasm *dasm, int i, t_op *o)
{
	int				j;
	int				nb;
	unsigned int	nb_inst;
	int				op;

	j = 0;
	nb_inst = dasm->buf[i + 1];
	op = dasm->buf[i];
	if (op < 1 || op > 16 || (nb_inst < 1 && o[op - 1].nb_arg != 1))
		return (return_f("FATAL ERROR : unknown opcode\n", -1));
	j = write_opcode(dasm, op, o);
	if (o[op - 1].nb_arg > 1)
	{
		if ((nb = write_big_arg(dasm, nb_inst, change_op_n(i, j, op), o)) == -1)
			return (return_f("FATAL ERROR : pb instuct\n", -1));
		i = nb;
	}
	else
	{
		if ((nb = write_small_arg(dasm, change_op_n(i, j, op), o)) == -1)
			return (return_f("FATAL ERROR : pb instuct\n", -1));
		i = i + nb + 1;
	}
	return (i);
}

int				then(t_dasm *dasm, t_op *op_tab)
{
	int		i;
	int		bis;

	dasm->nb_tab = 2;
	i = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	while (i < dasm->ret)
	{
		if ((bis = instruct_alone(dasm, i, op_tab)) == -1)
			return (-1);
		i = bis;
		dasm->nb_tab++;
	}
	if (i != dasm->ret)
		return (-1);
	return (0);
}
