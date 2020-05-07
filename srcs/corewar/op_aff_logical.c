/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:20:55 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/06 17:33:55 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	ft_aff(t_cw *cw, t_process *prcs, int i, t_op op)
{
	t_arg	arg;

	(void)i;
	(void)cw;
	(void)op;
	arg = prcs->arg;
	prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
}

void	ft_and(t_cw *cw, t_process *prcs, int j, t_op op)
{
	unsigned char	a[MAX_SIZE];
	unsigned char	b[MAX_SIZE];
	t_arg			arg;

	arg = prcs->arg;
	j = -1;
	while (++j < DIR_SIZE)
	{
		a[j] = arg.value[0][j];
		if (arg.type[0] == REG_CODE)
			a[j] = prcs->reg[arg.intv[0] - 1][j];
		else if (arg.type[0] == IND_CODE)
			a[j] = cw->arena[(prcs->pc + arg.intv[0] % IDX_MOD) % MEM_SIZE];
		b[j] = arg.value[1][j];
		if (arg.type[1] == REG_CODE)
			b[j] = prcs->reg[arg.intv[1] - 1][j];
		else if (arg.type[1] == IND_CODE)
			b[j] = cw->arena[(prcs->pc + arg.intv[1] % IDX_MOD) % MEM_SIZE];
		prcs->reg[arg.intv[2] - 1][j] = a[j] & b[j];
	}
	ft_printf("P%s%u | %s %d %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1,
		op.name, arg.real_value[0], arg.real_value[1], arg.intv[2]);
	prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
	prcs->carry =
		(ft_str_to_int(prcs->reg[arg.intv[2] - 1], REG_SIZE) == 0) ? 1 : 0;
}

void	ft_or(t_cw *cw, t_process *prcs, int j, t_op op)
{
	unsigned char	a[MAX_SIZE];
	unsigned char	b[MAX_SIZE];
	t_arg			arg;

	arg = prcs->arg;
	j = -1;
	while (++j < DIR_SIZE)
	{
		a[j] = arg.value[0][j];
		if (arg.type[0] == REG_CODE)
			a[j] = prcs->reg[arg.intv[0] - 1][j];
		else if (arg.type[0] == IND_CODE)
			a[j] = cw->arena[(prcs->pc + arg.intv[0] % IDX_MOD) % MEM_SIZE];
		b[j] = arg.value[1][j];
		if (arg.type[1] == REG_CODE)
			b[j] = prcs->reg[arg.intv[1] - 1][j];
		else if (arg.type[1] == IND_CODE)
			b[j] = cw->arena[(prcs->pc + arg.intv[1] % IDX_MOD) % MEM_SIZE];
		prcs->reg[arg.intv[2] - 1][j] = a[j] | b[j];
	}
	ft_printf("P%s%u | %s %d %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1,
		op.name, arg.real_value[0], arg.real_value[1], arg.intv[2]);
	prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
	prcs->carry =
		(ft_str_to_int(prcs->reg[arg.intv[2] - 1], REG_SIZE) == 0) ? 1 : 0;
}

void	ft_xor(t_cw *cw, t_process *prcs, int j, t_op op)
{
	unsigned char	a[MAX_SIZE];
	unsigned char	b[MAX_SIZE];
	t_arg			arg;

	arg = prcs->arg;
	j = -1;
	while (++j < DIR_SIZE)
	{
		a[j] = arg.value[0][j];
		if (arg.type[0] == REG_CODE)
			a[j] = prcs->reg[arg.intv[0] - 1][j];
		else if (arg.type[0] == IND_CODE)
			a[j] = cw->arena[(prcs->pc + arg.intv[0] % IDX_MOD) % MEM_SIZE];
		b[j] = arg.value[1][j];
		if (arg.type[1] == REG_CODE)
			b[j] = prcs->reg[arg.intv[1] - 1][j];
		else if (arg.type[1] == IND_CODE)
			b[j] = cw->arena[(prcs->pc + arg.intv[1] % IDX_MOD) % MEM_SIZE];
		prcs->reg[arg.intv[2] - 1][j] = a[j] ^ b[j];
	}
	prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
	ft_printf("P%s%u | %s %d %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1,
		op.name, arg.real_value[0], arg.real_value[1], arg.intv[2]);
	prcs->carry = (ft_str_to_int(prcs->reg[arg.intv[2] - 1],
		REG_SIZE) == 0) ? 1 : 0;
}
