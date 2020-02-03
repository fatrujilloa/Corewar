/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:49:40 by rbeaufre          #+#    #+#             */
/*   Updated: 2020/02/03 00:49:39 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		ft_declare_winner(t_cw *cw,int n)
{
	ft_printf("It is now cycle %d\n", cw->nb_cycles);
	if (n == -1)
		ft_printf("No champion called the instruction alive\n");
	else
		ft_printf("Le joueur %d(%s) a gagné\n", n, cw->champ[n].name);
}

void		ft_exec_processes(t_cw *cw, t_process *prcs)
{
	unsigned char	op_code;

	while (prcs)
	{
		//ft_printf("The process #%u has PC = %u\n", prcs->nb + 1, prcs->pc);
		op_code = (unsigned char)cw->arena[prcs->pc];
		if (cw->nb_cycles < prcs->wait_until)
		{	
			prcs = prcs->next;
			continue ;
		}
		if (!(op_code == 0 || op_code > 16))
		{
			if (cw->nb_cycles == prcs->wait_until && prcs->valid_arg == 1)
				op_tab[op_code - 1].function(cw, prcs, prcs->champ, op_tab[op_code - 1]);
			else if (cw->nb_cycles == prcs->wait_until)
				prcs->pc = (prcs->pc + prcs->arg.total_size) % MEM_SIZE;
			else
			{
				prcs->wait_until = cw->nb_cycles + op_tab[op_code - 1].cycle - 1;
				ft_get_args(cw, prcs, &prcs->arg, op_tab[op_code - 1]);
			}
		}
		else
			prcs->pc = (prcs->pc + 1) % MEM_SIZE;
		prcs = prcs->next;
	}
}

void		ft_check_processes(t_cw *cw, t_process **head_prcs)
{
	t_process	*tmp;

	while(head_prcs && *head_prcs && (*head_prcs)->alive == 0)
	{
		cw->nb_prcs--;
		ft_lstdelnext(head_prcs, NULL);
	}
	if (!head_prcs || !*head_prcs)
		return ;
	tmp = *head_prcs;
	while (tmp)
	{
		if (tmp->next && tmp->next->alive == 0)
		{
			cw->nb_prcs--;
			ft_lstdelnext(head_prcs, &tmp);
		}
		else
		{
			tmp->alive = 0;
			tmp = tmp->next;
		}
	}
}

int			ft_cw(t_cw *cw)
{
	int			live_counter;

	live_counter = 0;
	while(cw->nbr_cycles_to_die > 0 && (!cw->dump_flag || cw->nb_cycles < cw->dump))
	{
		cw->nb_cycles++;
		ft_printf("It is now cycle %d\n", cw->nb_cycles);
		ft_exec_processes(cw, cw->prcs);
		if (cw->nb_cycles % cw->nbr_cycles_to_die == 0)
		{
			live_counter++;
			if ((live_counter % NBR_LIVE) == 0)
				cw->nbr_cycles_to_die -= CYCLE_DELTA;
			ft_check_processes(cw, cw->head);
			if (cw->nb_prcs <= 1)
				return (cw->last_alive);
		}
	}
	return (cw->last_alive);
}

void	ft_reverse_champ_nbrs(t_cw *cw)
{
	int			i;
	t_process	*prcs;

	i = -1;
	prcs = cw->prcs;
	while (++i < cw->nb_players)
	{
		cw->champ_nbrs[i] = 4294967295 - cw->champ_nbrs[i];
		*(unsigned int*)prcs->reg[0] = cw->champ_nbrs[i];
		ft_strnrev(prcs->reg[0], REG_SIZE);
		prcs = prcs->next;
	}
}

int			main(int argc, char **argv)
{
	t_cw	cw;
	int		winner;

	if (argc == 1 && ft_display_options())
		return (0);
	ft_init_corewar(argv, &cw);
	ft_reverse_champ_nbrs(&cw);
	if (cw.dump_flag == 1 && cw.dump == 0)
	{
		ft_print_arena(&cw);
		return (0);
	}
	winner = ft_cw(&cw);
	if (cw.dump_flag == 0)
		ft_declare_winner(&cw, winner);
	else
		ft_print_arena(&cw);
	return (0);
}