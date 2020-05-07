/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:11:01 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/06 20:40:12 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

unsigned int	ft_recover_value_arena(t_cw *cw, int pc, int size)
{
	int				i;
	unsigned int	v;

	i = -1;
	v = 0;
	while (++i < size)
		v = (256 * v + (unsigned char)cw->arena[(pc + i) % MEM_SIZE]);
	return (v);
}

void			ft_real_values(t_cw *cw, t_process *prcs, t_arg *arg)
{
	int i;
	int aux;

	aux = 2;
	i = -1;
	while (++i < arg->nb_args && arg->size[i])
	{
		if (arg->type[i] == REG_CODE)
			arg->real_value[i] =
				ft_str_to_int(prcs->reg[arg->intv[i] - 1], REG_SIZE);
		else if (arg->type[i] == IND_CODE)
			arg->real_value[i] = ft_recover_value_arena(cw,
				(prcs->pc + arg->intv[i]) % MEM_SIZE, REG_SIZE);
		else
			arg->real_value[i] = arg->intv[i];
		aux += arg->size[i];
	}
}

void			ft_arg_value(t_cw *cw, int pc, t_arg *arg, int i)
{
	int				j;
	unsigned int	v;

	v = 0;
	j = -1;
	while (++j < arg->size[i])
	{
		arg->value[i][j] = (unsigned char)cw->arena[(pc + j) % MEM_SIZE];
		v = 256 * v + arg->value[i][j];
	}
	arg->intv[i] = v;
}

void			ft_arg_values(t_cw *cw, t_process *prcs, t_arg *arg)
{
	int i;
	int aux;

	aux = 2;
	i = -1;
	while (++i < arg->nb_args)
	{
		ft_arg_value(cw, (prcs->pc + aux) % MEM_SIZE, arg, i);
		if (arg->type[i] == REG_CODE && (arg->intv[i] == 0 ||
			arg->intv[i] > REG_NUMBER))
		{
			prcs->valid_arg = -1;
			return ;
		}
		aux = aux + arg->size[i];
	}
}
