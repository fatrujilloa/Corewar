/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live_st_zjmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 18:14:33 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/06 18:25:15 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	ft_live(t_cw *cw, t_process *prcs, int i, t_op op)
{
	int				j;

	(void)i;
	j = -1;
	ft_printf("P%s%u | %s %d\n", ft_spaces(prcs->nb + 1),
		prcs->nb + 1, op.name, prcs->arg.intv[0]);
	while (++j < cw->nb_players)
	{
		if (prcs->arg.intv[0] == cw->champ_nbrs[j])
		{
			cw->alive[j] = 1;
			cw->last_alive = j;
			ft_printf("Player %d (%s) is said to be alive\n",
				j + 1, cw->champ[j].name);
			break ;
		}
	}
	cw->live_counter++;
	prcs->alive = 1;
	prcs->pc = (prcs->pc + 1 + DIR_SIZE) % MEM_SIZE;
}

void	ft_st(t_cw *cw, t_process *prcs, int i, t_op op)
{
	int		j;
	t_arg	arg;

	(void)i;
	arg = prcs->arg;
	j = -1;
	if (arg.type[1] == REG_CODE)
		while (++j < REG_SIZE)
			prcs->reg[arg.intv[1] - 1][j] = prcs->reg[arg.intv[0] - 1][j];
	else
		while (++j < REG_SIZE)
			cw->arena[((prcs->pc + j + (short int)arg.intv[1] % IDX_MOD)
				% MEM_SIZE + MEM_SIZE) % MEM_SIZE] =
			prcs->reg[arg.intv[0] - 1][j];
	ft_printf("P%s%u | %s r%d %d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1,
		op.name, arg.intv[0], (short int)arg.intv[1]);
	prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
}

void	ft_sti(t_cw *cw, t_process *prcs, int j, t_op op)
{
	int				address_int;
	unsigned int	address_uint;
	t_arg			a;

	a = prcs->arg;
	address_int = (prcs->pc + ((a.type[1] == DIR_CODE ?
		(short int)a.real_value[1] : (int)a.real_value[1])
		+ (a.type[2] == DIR_CODE ? (short int)a.real_value[2]
		: (int)a.real_value[2])) % IDX_MOD);
	address_uint = (address_int % MEM_SIZE + MEM_SIZE) % MEM_SIZE;
	j = -1;
	while (++j < REG_SIZE)
		cw->arena[(address_uint + j) % MEM_SIZE] = prcs->reg[a.intv[0] - 1][j];
	ft_printf("P%s%u | %s r%d %d %d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1,
	op.name, a.intv[0], (a.type[1] == DIR_CODE
	? (short int)a.real_value[1] : (int)a.real_value[1]), (a.type[2] == DIR_CODE
	? (short int)a.real_value[2] : (int)a.real_value[2]));
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
	(a.type[1] == DIR_CODE ? (short int)a.real_value[1] : (int)a.real_value[1]),
	(a.type[2] == DIR_CODE ? (short int)a.real_value[2] : (int)a.real_value[2]),
	(a.type[1] == DIR_CODE ? (short int)a.real_value[1] : (int)a.real_value[1])
	+ (a.type[2] == DIR_CODE ? (short int)a.real_value[2]
	: (int)a.real_value[2]), address_int);
	prcs->pc = (prcs->pc + a.total_size) % MEM_SIZE;
	ft_update_process(cw, prcs, op);
}

void	ft_zjmp(t_cw *cw, t_process *prcs, int i, t_op op)
{
	int				int_address;
	unsigned int	uint_address;
	t_arg			arg;

	(void)i;
	(void)cw;
	arg = prcs->arg;
	int_address = (prcs->pc + (short int)arg.intv[0] % IDX_MOD) % MEM_SIZE;
	uint_address = (int_address + MEM_SIZE) % MEM_SIZE;
	if (prcs->carry)
	{
		ft_printf("P%s%u | %s %hd OK\n", ft_spaces(prcs->nb + 1),
			prcs->nb + 1, op.name, arg.intv[0]);
		prcs->pc = uint_address;
	}
	else
	{
		ft_printf("P%s%u | %s %hd FAILED\n", ft_spaces(prcs->nb + 1),
			prcs->nb + 1, op.name, arg.intv[0]);
		prcs->pc = (prcs->pc + 1 + IND_SIZE) % MEM_SIZE;
	}
}
