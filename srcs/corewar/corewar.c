/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:49:40 by rbeaufre          #+#    #+#             */
/*   Updated: 2020/01/28 01:42:41 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	ft_print_prcs(t_process *prcs)
{
	ft_printf("Printing process:\n");
	ft_printf("Carry = %d, PC = %d, Wait_until = %d, alive = %d\n", prcs->carry, prcs->pc, prcs->wait_until, prcs->alive);
	if (!prcs->next)
		{
			ft_printf("prcs->next = NULL\n");
			//free(prcs);
			//ft_printf("We freed prcs\n");
		}
}

void	ft_lstdelnext(t_process **lst, t_process **prev)
{
	t_process	*tmp;

	//ft_printf("Deleting process\n");
	if (!lst || !(*lst))
		return ;
	if (!prev)
	{
		//ft_print_prcs(*lst);
		//ft_printf("Deleting HEAD\n");
		tmp = *lst;
		*lst = tmp->next ? tmp->next : NULL;
		//free(tmp);
		return ;
	}
	if ((tmp = (*prev)->next) == NULL)
		return ;
	(*prev)->next = tmp->next;
	//free(tmp);
}

void		ft_print_arena(t_cw *cw)
{
	int s;
	int i;

	s = 0;
	while (s * s < MEM_SIZE)
		s++;
	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%02x ", (unsigned char)cw->arena[i]);
		i++;
		if (i % s == 0)
			ft_putchar('\n');
	}
}

void		ft_exec_processes(t_cw *cw, t_process *prcs, int i)
{
	int j = 1;
	unsigned char	op_code;

	while (prcs)
	{
		//ft_printf("The process #%d of player %d(%s) has PC = %d and wait_until = %d\n", j, i, cw->champ[i].name, prcs->pc, prcs->wait_until);
		op_code = (unsigned char)cw->arena[prcs->pc];
		if (cw->nb_cycles < prcs->wait_until)
			prcs = prcs->next;
		else if (op_code == 0 || op_code > 16) //op_code > 16
		{
			prcs->pc++;
			prcs = prcs->next;	
		}
		else
		{		
			//ft_printf("Executing action with op_code = %d\n", op_code);
			op_tab[op_code - 1].function(cw, prcs, i, op_tab[op_code - 1]);
			prcs = prcs->next;
		}
		j++;
	}
}

void		ft_check_processes(t_cw *cw, t_process *prcs, int i)
{
	t_process	**head_prcs;

	//ft_printf("Now checking processes. The number of processes is %d\n", cw->nb_prcs);
	//ft_print_prcs(prcs);
	head_prcs = &prcs;
	(void)i;
	while(head_prcs && *head_prcs && (*head_prcs)->alive == 0)
	{
		//ft_printf("Testing process with alive = %d\n", (*head_prcs)->alive);
		cw->nb_prcs--;
		//ft_printf("Deleting head\n");
		ft_lstdelnext(head_prcs, NULL);
		/*
		if (!prcs)
			ft_printf("Sucessfuly deleted one head\n");
		*/
	}
	//	ft_printf("OUT\n");
	if (!head_prcs || !*head_prcs)
		return ;
	prcs = *head_prcs;
	while (prcs)
	{
		if (prcs->next && prcs->next->alive == 0)
		{
			cw->nb_prcs--;
			ft_lstdelnext(head_prcs, &prcs);
			//ft_printf("Deleting node\n");
		}
		else
		{
			prcs->alive = 0;
			prcs = prcs->next;
		}
	}
}

int			ft_cw(t_cw *cw)
{
	int		i;
	int		live_counter;

	live_counter = 0;
	while(cw->nbr_cycles_to_die > 0 && (cw->dump_flag == - 1 || cw->nb_cycles < cw->dump_flag))
	{
		cw->nb_cycles++;
		//ft_printf("Currently at cycle %d\n", cw->nb_cycles);
		//ft_print_arena(cw);
		if (cw->nb_cycles % cw->nbr_cycles_to_die == 0)
		{
			live_counter++;
			i = -1;
			while (++i < cw->nb_players)
				ft_check_processes(cw, cw->prcs[i], i);
			if (cw->nb_prcs <= 1)
				return (cw->last_alive);
			if ((live_counter % NBR_LIVE) == 0)
				cw->nbr_cycles_to_die -= CYCLE_DELTA;
				ft_printf("Reduction of cycles_to_die\n");
		}
		i = -1;
		while (i++ < cw->nb_players)
			ft_exec_processes(cw, cw->prcs[i], i);
	}
	return (cw->last_alive);
}

static int	ft_process_args(int argc, char **argv, t_cw *cw)
{
	cw->first_champ_i = ft_scan_flags(argc, argv, cw);
	cw->nb_players = ft_init_champs(argc, argv, cw);
	return (1);
}

void		ft_declare_winner(t_cw *cw,int n)
{
	ft_printf("Currently at cycle %d\n", cw->nb_cycles);
	if (n == -1)
		ft_printf("No champion called the instruction alive\n");
	else
		ft_printf("Le joueur %d(%s) a gagné\n", n, cw->champ[n].name);
}

int			main(int argc, char **argv)
{
	t_cw	cw;
	int		winner;

	if (argc == 1 && ft_display_options())
		return (0);
	ft_process_args(argc, argv, &cw);
	ft_init_cw(&cw);

	/*
	ft_printf("Le flag dump_flag est fixe a %i\n", cw.dump_flag);
	ft_printf("Le flag number_flag est fixe a %i\n", cw.number_flag);
	ft_printf("{GREEN}Name{EOC}\n");
	ft_print_hexa(cw.champ[0].name, PROG_NAME_LENGTH);
	ft_printf("{GREEN}Comment{EOC}\n");
	ft_print_hexa(cw.champ[0].comment, COMMENT_LENGTH);
	ft_printf("{GREEN}Content{EOC}\n");
	ft_print_hexa(cw.champ[0].content, CHAMP_MAX_SIZE);
	*/

	winner = ft_cw(&cw);
	if (cw.dump_flag == -1)
		ft_declare_winner(&cw, winner);
	else
		ft_print_arena(&cw);
	return (0);
}
