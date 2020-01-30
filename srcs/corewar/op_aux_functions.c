/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aux_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 22:52:26 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/30 22:57:57 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int     ft_new_prcs(t_process **lst, int new_pc)
{
	int			j;
	t_process	*process;
	t_process	*new_process;

	process = *lst;
	while (process->next)
		process = process->next;
	if (!(process->next = (t_process*)ft_memalloc(sizeof(t_process))))
        return (0);
	new_process = process->next;
	new_process->pc = new_pc;
	new_process->carry = process->carry;
	new_process->wait_until = process->wait_until;
	new_process->alive = 0;
	process->next = NULL;
    process->valid_arg = 0;
	j = -1;
	while (++j < REG_NUMBER)
		ft_bzero(process->reg[j], REG_SIZE);
    ft_init_arg(&new_process->arg, 0);
    return (1);
}

void    ft_update_process(t_cw *cw, t_process *prcs, t_op op)
{
    (void)(cw);
    
    prcs->carry = op.carry ? op.carry : prcs->carry;
   // prcs->wait_until = cw->nb_cycles + op.cycle;
    prcs = prcs->next;
}

unsigned int    ft_str_to_int(unsigned char *str, unsigned int size)
{
    unsigned int    i;
    unsigned int    v;

    v = 0;
    i = 0;
    while (i < size)
        v = 256 * v + str[i++];
    return (v);
}


unsigned int    ft_ind_arg(t_cw *cw, int pc)
{
    int             i;
    unsigned int    v;

    i = -1;
    v = 0;
    while (++i < IND_SIZE)
        v = (256 * v + (unsigned char)cw->arena[(pc + i) % MEM_SIZE]) % MEM_SIZE;
    return (v);
}

