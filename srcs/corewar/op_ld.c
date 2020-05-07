/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:58:18 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/06 18:11:27 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	ft_ld(t_cw *cw, t_process *prcs, int i, t_op op)
{
	int		j;
	t_arg	arg;

	(void)i;
	(void)cw;
	arg = prcs->arg;
	j = -1;
	if (arg.type[0] == IND_CODE)
		while (++j < REG_SIZE)
			prcs->reg[arg.intv[1] - 1][j] =
				cw->arena[((prcs->pc + j + (short int)arg.intv[0] % IDX_MOD)
					% MEM_SIZE + MEM_SIZE) % MEM_SIZE];
	else
		while (++j < DIR_SIZE)
			prcs->reg[arg.intv[1] - 1][j] = arg.value[0][j];
	ft_printf("P%s%u | %s %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1,
		op.name, arg.type[0] == IND_CODE ? ft_recover_value_arena(cw,
		((prcs->pc + (short int)arg.intv[0] % IDX_MOD) % MEM_SIZE + MEM_SIZE)
		% MEM_SIZE, REG_SIZE) : arg.real_value[0], arg.intv[1]);
	prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
	prcs->carry = (arg.real_value[0] == 0) ? 1 : 0;
}

void	ft_lld(t_cw *cw, t_process *prcs, int i, t_op op)
{
	int		j;
	t_arg	arg;

	(void)i;
	(void)cw;
	arg = prcs->arg;
	j = -1;
	if (arg.type[0] == IND_CODE)
	{
		*(unsigned int*)prcs->reg[arg.intv[1] - 1] = arg.real_value[0] / 65536;
		ft_strnrev(prcs->reg[arg.intv[1] - 1], 4);
		ft_printf("P%s%u | %s %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1,
			op.name, arg.real_value[0] / 65536, arg.intv[1]);
	}
	else
	{
		while (++j < DIR_SIZE)
			prcs->reg[arg.intv[1] - 1][j] = arg.value[0][j];
		ft_printf("P%s%u | %s %d r%d\n", ft_spaces(prcs->nb + 1),
			prcs->nb + 1, op.name, arg.real_value[0], arg.intv[1]);
	}
	prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
	prcs->carry = (arg.real_value[0] == 0) ? 1 : 0;
}

void	ft_ldi(t_cw *cw, t_process *prcs, int j, t_op op)
{
	int				address_int;
	unsigned int	address_uint;
	t_arg			a;

	a = prcs->arg;
	address_int = (prcs->pc + ((a.type[0] == DIR_CODE ?
		(short int)a.real_value[0] : (int)a.real_value[0]) +
		(a.type[1] == DIR_CODE ? (short int)a.real_value[1]
		: (int)a.real_value[1])) % IDX_MOD);
	address_uint = (address_int % MEM_SIZE + MEM_SIZE) % MEM_SIZE;
	j = -1;
	while (++j < REG_SIZE)
		prcs->reg[a.intv[2] - 1][j] = cw->arena[(address_uint + j) % MEM_SIZE];
	ft_printf("P%s%u | %s %d %d r%d\n", ft_spaces(prcs->nb + 1),
	prcs->nb + 1, op.name,
	(a.type[0] == DIR_CODE ? (short int)a.real_value[0] : (int)a.real_value[0]),
	(a.type[1] == DIR_CODE ? (short int)a.real_value[1] : (int)a.real_value[1]),
	a.intv[2]);
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
	(a.type[0] == DIR_CODE ? (short int)a.real_value[0] : (int)a.real_value[0]),
	(a.type[1] == DIR_CODE ? (short int)a.real_value[1] : (int)a.real_value[1]),
	(a.type[0] == DIR_CODE ? (short int)a.real_value[0] : (int)a.real_value[0])
	+ (a.type[1] == DIR_CODE ? (short int)a.real_value[1]
	: (int)a.real_value[1]), address_int);
	prcs->pc = (prcs->pc + a.total_size) % MEM_SIZE;
}

void	ft_lldi(t_cw *cw, t_process *prcs, int i, t_op op)
{
	int				j;
	int				address_int;
	unsigned int	address_uint;
	t_arg			arg;

	(void)i;
	arg = prcs->arg;
	address_int = (prcs->pc + (int)arg.real_value[0] + (int)arg.real_value[1])
		% MEM_SIZE;
	address_uint = (address_int + MEM_SIZE) % MEM_SIZE;
	j = -1;
	while (++j < REG_SIZE)
		prcs->reg[arg.intv[2] - 1][j] =
		cw->arena[(address_uint + j) % MEM_SIZE];
	ft_printf("P%s%u | %s %d %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1,
		op.name, arg.real_value[0], arg.real_value[1], arg.intv[2]);
	ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
		arg.real_value[0], arg.real_value[1], arg.real_value[0]
		+ arg.real_value[1], prcs->pc + (int)arg.real_value[0]
		+ (int)arg.real_value[1]);
	prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
	prcs->carry =
		(ft_str_to_int(prcs->reg[arg.intv[2] - 1], REG_SIZE) == 0) ? 1 : 0;
}
