/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 20:36:48 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/06 20:40:07 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int				ft_check_operation_2(t_process *prcs, t_op op)
{
	t_arg	*arg;

	arg = &prcs->arg;
	if (op.opcode == 10)
		return ((arg->type[1] != REG_CODE && arg->type[1] != DIR_CODE)
		|| arg->type[2] != REG_CODE);
		if (op.opcode == 11)
		return ((arg->type[2] != REG_CODE && arg->type[2] != DIR_CODE)
		|| arg->type[0] != REG_CODE);
		if (op.opcode == 13)
		return ((arg->type[0] != DIR_CODE && arg->type[0] != IND_CODE)
		|| arg->type[1] != REG_CODE);
		if (op.opcode == 14)
		return ((arg->type[1] != REG_CODE && arg->type[1] != DIR_CODE)
		|| arg->type[2] != REG_CODE);
		if (op.opcode == 16)
		return (arg->type[0] != REG_CODE);
	return (0);
}

int				ft_check_operation(t_process *prcs, t_op op)
{
	t_arg	*arg;

	arg = &prcs->arg;
	if ((op.opcode == 1) || (op.opcode == 9) || (op.opcode == 12)
		|| (op.opcode == 15))
		return (1);
	if (op.opcode == 2)
		return ((arg->type[0] != DIR_CODE && arg->type[0] != IND_CODE)
		|| arg->type[1] != REG_CODE);
		if (op.opcode == 3)
		return ((arg->type[1] != IND_CODE && arg->type[1] != REG_CODE)
		|| arg->type[0] != REG_CODE);
		if (op.opcode == 4)
		return (arg->type[0] != REG_CODE || arg->type[1] != REG_CODE
		|| arg->type[2] != REG_CODE);
		if (op.opcode == 5)
		return (arg->type[0] != REG_CODE || arg->type[1] != REG_CODE
		|| arg->type[2] != REG_CODE);
		if (op.opcode == 6 || op.opcode == 7 || op.opcode == 8)
		return (arg->type[2] != REG_CODE);
	return (ft_check_operation_2(prcs, op));
}
