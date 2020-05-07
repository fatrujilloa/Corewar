/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:31:28 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/07 03:01:36 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		ft_exec_processes(t_cw *cw, t_process *prcs)
{
	unsigned char	op_code;

	while (prcs)
	{
		if (cw->nb_cycles < prcs->wait_until && ((prcs = prcs->next) || (1)))
			continue ;
		op_code = (unsigned char)cw->arena[prcs->pc];
		if (cw->nb_cycles == prcs->wait_until)
		{
			ft_get_args(cw, prcs, &prcs->arg, g_op_tab[prcs->current_op - 1]);
			if (prcs->valid_arg == 1)
				g_op_tab[prcs->current_op - 1].function(cw, prcs, prcs->champ,
					g_op_tab[prcs->current_op - 1]);
			else if (cw->nb_cycles == prcs->wait_until)
				prcs->pc = (prcs->pc + prcs->arg.total_size) % MEM_SIZE;
		}
		else if (!(op_code == 0 || op_code > 16))
		{
			prcs->current_op = op_code;
			prcs->wait_until = cw->nb_cycles + g_op_tab[op_code - 1].cycle - 1;
		}
		else
			prcs->pc = (prcs->pc + 1) % MEM_SIZE;
		prcs = prcs->next;
	}
}

void		ft_check_processes(t_cw *cw, t_process **head_prcs)
{
	t_process	*tmp;

	while (head_prcs && *head_prcs && (*head_prcs)->alive == 0)
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

void		ft_check_champions(t_cw *cw, t_process *prcs)
{
	int i;

	i = -1;
	while (++i < cw->nb_players)
	{
		if (cw->alive[i])
		{
			cw->alive[i] = 0;
			continue ;
		}
		while (prcs)
		{
			if (prcs->champ == i)
				prcs->alive = 0;
			prcs = prcs->next;
		}
	}
}

int			ft_cw(t_cw *cw)
{
	while ((!cw->dump_flag || cw->nb_cycles < cw->dump))
	{
		cw->nb_cycles++;
		ft_printf("It is now cycle %d\n", cw->nb_cycles);
		ft_exec_processes(cw, cw->prcs);
		if ((cw->nb_cycles - cw->last_wipe) % cw->nbr_cycles_to_die == 0
			|| cw->nbr_cycles_to_die <= 0)
		{
			ft_check_processes(cw, &cw->prcs);
			if (cw->live_counter >= NBR_LIVE || cw->nb_checks >= MAX_CHECKS)
			{
				cw->nbr_cycles_to_die -= CYCLE_DELTA;
				cw->nb_checks = 0;
				ft_printf("Cycle to die is now %d\n", cw->nbr_cycles_to_die);
			}
			cw->last_wipe = cw->nb_cycles;
			cw->live_counter = 0;
			cw->nb_checks++;
		}
		if (cw->nb_prcs == 0)
			return (cw->last_alive);
	}
	return (cw->last_alive);
}

int			main(int argc, char **argv)
{
	t_cw	cw;
	int		winner;
	int		i;

	if (argc == 1 && ft_display_options())
		return (0);
	ft_init_corewar(argv, &cw, -1);
	ft_printf("Introducing contestants...\n");
	i = -1;
	while (++i < cw.nb_players)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		4294967296 - cw.champ_nbrs[i], cw.champ[i].size, cw.champ[i].name,
		cw.champ[i].comment);
	if (cw.dump_flag == 1 && cw.dump == 0)
	{
		ft_print_arena(&cw);
		return (0);
	}
	winner = ft_cw(&cw);
	if (cw.dump_flag == 0)
		ft_printf("Contestant %d, \"%s\", has won !\n",
		4294967296 - cw.champ_nbrs[winner], cw.champ[winner].name);
	else
		ft_print_arena(&cw);
	return (0);
}
