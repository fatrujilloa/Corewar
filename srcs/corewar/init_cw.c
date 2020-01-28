/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 13:15:36 by rbeaufre          #+#    #+#             */
/*   Updated: 2020/01/28 01:07:52 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		ft_init_processes(t_cw *cw)
{
	int			i;
	int			j;
	t_process	*process;

	i = -1;
	while (++i < cw->nb_players)
	{
		cw->prcs[i] = (t_process*)ft_memalloc(sizeof(t_process));
		process = cw->prcs[i];
		process->pc = 0;
		process->carry = 0;
		process->wait_until = 0;
		process->alive = 0;
		process->next = NULL;
		j = -1;
		while (++j < REG_NUMBER)
			ft_bzero(process->reg[j], REG_SIZE);
	}
}

void		ft_init_arena(t_cw *cw)
{
	int	i;

	ft_bzero(cw->arena, 4096);
	i = -1;
	while (++i < cw->nb_players)
		ft_memcpy(&cw->arena[i * (MEM_SIZE / cw->nb_players)],
			cw->champ[i].content, CHAMP_MAX_SIZE);
	/*
	i = 0;
	while (++i < cw->nb_players - 1)
		ft_memcpy(&cw->arena[i * (MEM_SIZE / cw->nb_players)],
			cw->champ[i].content, CHAMP_MAX_SIZE);
	cw->arena[0] = 4
	cw->arena[1] = 53
	cw->arena[2] = 2
	cw->arena[3] = 3
	cw->arena[4] = 4
	*/
}

int			ft_init_cw(t_cw *cw)
{
	cw->nb_cycles = 0;
	cw->nbr_cycles_to_die = CYCLE_TO_DIE;
	cw->nb_prcs = cw->nb_players;
	cw->last_alive = -1;
	ft_init_processes(cw);
	ft_init_arena(cw);
	return (1);
}
