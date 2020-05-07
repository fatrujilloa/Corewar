/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aux_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:46:47 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/06 17:47:56 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int				ft_new_process(t_cw *cw, t_process **head,
								t_process *prcs, int new_pc)
{
	int			j;
	t_process	*new_prcs;

	if (!(new_prcs = (t_process*)ft_memalloc(sizeof(t_process))))
		exit(ft_printf("Malloc failed"));
	new_prcs->pc = new_pc;
	new_prcs->carry = prcs->carry;
	new_prcs->wait_until = prcs->wait_until;
	new_prcs->alive = prcs->alive;
	new_prcs->next = *head;
	new_prcs->champ = prcs->champ;
	new_prcs->champ_nb = prcs->champ_nb;
	new_prcs->nb = cw->last_prcs++;
	new_prcs->valid_arg = 0;
	j = -1;
	while (++j < REG_NUMBER)
		ft_memcpy(new_prcs->reg[j], prcs->reg[j], REG_SIZE);
	ft_init_arg(&new_prcs->arg, 0);
	cw->prcs = new_prcs;
	return (1);
}

void			ft_update_process(t_cw *cw, t_process *prcs, t_op op)
{
	(void)(cw);
	if (op.carry)
		prcs->carry = 1;
}

unsigned int	ft_str_to_int(unsigned char *str, unsigned int size)
{
	unsigned int	i;
	unsigned int	v;

	v = 0;
	i = 0;
	while (i < size)
		v = 256 * v + str[i++];
	return (v);
}

unsigned int	ft_ind_arg(t_cw *cw, int pc)
{
	int				i;
	unsigned int	v;

	i = -1;
	v = 0;
	while (++i < IND_SIZE)
		v = (256 * v + (unsigned char)cw->arena[(pc + i) % MEM_SIZE]);
	return (v % MEM_SIZE);
}
