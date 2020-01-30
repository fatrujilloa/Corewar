/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_forks_add_sub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:50:25 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/30 22:55:22 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"


void    ft_add(t_cw *cw, t_process *prcs, int i, t_op op) //    3 REG
{
    int             j;
    int             carry;
    int             tmp;
    t_arg   arg;
    
    arg = prcs->arg;
    j = REG_SIZE;
    carry = 0;
    while (--j >= 0)
    {
        tmp = prcs->reg[arg.int_value[0] - 1][j]
            + prcs->reg[arg.int_value[1] - 1][j] + carry;
        carry = (tmp < 256) ? 0 : 1;
        prcs->reg[arg.int_value[2] - 1][j] = tmp % 256;
    }
    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    ft_update_process(cw, prcs, op);
}

void    ft_sub(t_cw *cw, t_process *prcs, int i, t_op op) // 3 REG
{
    int             j;
    int             carry;
    int             tmp;
    unsigned char   neg[REG_SIZE];
    t_arg   arg;
    
    arg = prcs->arg;
    j = REG_SIZE;
    carry = 0;
    while (--j >= 0)
    {
        tmp = (256 - prcs->reg[arg.int_value[1] - 1][j] - carry) % 256;
        //ft_printf("prcs->reg[arg.int_value[1] - 1][%d] = %u, tmp = %d\n", j, prcs->reg[arg.int_value[1] - 1][j], tmp);
        carry = (tmp > 0) ? 1 : 0;
        neg[j] = tmp;
    }
    j = REG_SIZE;
    carry = 0;
    while (--j >= 0)
    {
        //ft_printf("neg[%d] = %u\n", j, neg[j]);
        tmp = prcs->reg[arg.int_value[0] - 1][j] + neg[j] + carry;
        carry = (tmp < 256) ? 0 : 1;
        prcs->reg[arg.int_value[2] - 1][j] = tmp % 256;
    }
    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    ft_update_process(cw, prcs, op);
}

void    ft_fork(t_cw *cw, t_process *prcs, int i, t_op op)
{
    int v;
    int j;

    //(void) i;

    v = 0;
    j = -1;
    while (++j < DIR_SIZE)
        v = (256 * v + (unsigned char)cw->arena
            [(prcs->pc + 1 + j) % MEM_SIZE]) % IDX_MOD;
    if (!ft_new_prcs(&prcs,(prcs->pc + v) % MEM_SIZE))
        return ; //I Have a malloc here
    cw->nb_prcs++;
    prcs->pc = (prcs->pc + 1 + DIR_SIZE) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    ft_update_process(cw, prcs, op);
}

void    ft_lfork(t_cw *cw, t_process *prcs, int i, t_op op)
{
    int v;
    int j;

    //(void) i;
    
    v = 0;
    j = -1;
    while (++j < DIR_SIZE)
        v = 256 * v + (unsigned char)cw->arena[(prcs->pc + 1 + j) % MEM_SIZE];
    if (!ft_new_prcs(&prcs,(prcs->pc + v) % MEM_SIZE))
        return ; //I Have a malloc here
    cw->nb_prcs++;
    prcs->pc = (prcs->pc + 1 + DIR_SIZE) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    ft_update_process(cw, prcs, op);
}
