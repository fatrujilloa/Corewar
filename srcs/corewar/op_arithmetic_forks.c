/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arithmetic_forks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:34:39 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/06 17:45:59 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	ft_add(t_cw *cw, t_process *prcs, int i, t_op op)
{
	int				j;
	int				carry;
	int				tmp;
	t_arg			arg;

	(void)i;
	(void)cw;
	arg = prcs->arg;
	j = REG_SIZE;
	carry = 0;
	while (--j >= 0)
	{
		tmp = prcs->reg[arg.intv[0] - 1][j]
			+ prcs->reg[arg.intv[1] - 1][j] + carry;
		carry = (tmp < 256) ? 0 : 1;
		prcs->reg[arg.intv[2] - 1][j] = tmp % 256;
	}
	ft_print_op(prcs, prcs->arg, op);
	prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
	prcs->carry =
		(ft_str_to_int(prcs->reg[arg.intv[2] - 1], REG_SIZE) == 0) ? 1 : 0;
}

void	ft_sub(t_cw *cw, t_process *prcs, int j, t_op op)
{
	int				carry;
	int				tmp;
	unsigned char	neg[REG_SIZE];

	(void)cw;
	j = REG_SIZE;
	carry = 0;
	while (--j >= 0)
	{
		tmp = (256 - prcs->reg[prcs->arg.intv[1] - 1][j] - carry) % 256;
		carry = (tmp > 0) ? 1 : 0;
		neg[j] = tmp;
	}
	j = REG_SIZE;
	carry = 0;
	while (--j >= 0)
	{
		tmp = prcs->reg[prcs->arg.intv[0] - 1][j] + neg[j] + carry;
		carry = (tmp < 256) ? 0 : 1;
		prcs->reg[prcs->arg.intv[2] - 1][j] = tmp % 256;
	}
	ft_print_op(prcs, prcs->arg, op);
	prcs->pc = (prcs->pc + prcs->arg.total_size) % MEM_SIZE;
	prcs->carry = (ft_str_to_int(prcs->reg[prcs->arg.intv[2] - 1],
		REG_SIZE) == 0) ? 1 : 0;
}

void	ft_fork(t_cw *cw, t_process *prcs, int i, t_op op)
{
	int				int_address;
	unsigned int	uint_address;
	t_arg			arg;

	(void)i;
	arg = prcs->arg;
	int_address = (prcs->pc + (short int)arg.intv[0] % IDX_MOD) % MEM_SIZE;
	uint_address = (int_address + MEM_SIZE) % MEM_SIZE;
	cw->nb_prcs++;
	ft_new_process(cw, cw->head, prcs, uint_address);
	ft_printf("P%s%u | %s %d (%d)\n", ft_spaces(prcs->nb + 1), prcs->nb + 1,
		op.name, (short int)arg.intv[0], int_address);
	prcs->pc = (prcs->pc + 1 + IND_SIZE) % MEM_SIZE;
}

void	ft_lfork(t_cw *cw, t_process *prcs, int i, t_op op)
{
	int				int_address;
	unsigned int	uint_address;
	t_arg			arg;

	(void)i;
	arg = prcs->arg;
	int_address = (prcs->pc + (short int)arg.intv[0]);
	uint_address = (int_address % MEM_SIZE + MEM_SIZE) % MEM_SIZE;
	cw->nb_prcs++;
	ft_new_process(cw, cw->head, prcs, uint_address);
	ft_printf("P%s%u | %s %d (%d)\n", ft_spaces(prcs->nb + 1), prcs->nb + 1,
		op.name, (short int)arg.intv[0], int_address);
	prcs->pc = (prcs->pc + 1 + IND_SIZE) % MEM_SIZE;
}
