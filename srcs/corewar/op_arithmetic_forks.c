/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arithmetic_forks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:50:25 by ftrujill          #+#    #+#             */
/*   Updated: 2020/02/04 02:08:44 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"


void    ft_add(t_cw *cw, t_process *prcs, int i, t_op op) //    3 REG
{
    int             j;
    int             carry;
    int             tmp;
    t_arg           arg;
    
    (void)i;
    (void)cw;
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
    ft_print_op(prcs, prcs->arg, op);
    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
    //ft_update_process(cw, prcs, op);
    prcs->carry = (ft_str_to_int(prcs->reg[arg.int_value[2] - 1], REG_SIZE) == 0) ? 1 : 0;
}

void    ft_sub(t_cw *cw, t_process *prcs, int i, t_op op) // 3 REG
{
    int             j;
    int             carry;
    int             tmp;
    unsigned char   neg[REG_SIZE];
    t_arg   arg;
    
    (void)i;
    (void)cw;
    arg = prcs->arg;
    j = REG_SIZE;
    carry = 0;
    while (--j >= 0)
    {
        tmp = (256 - prcs->reg[arg.int_value[1] - 1][j] - carry) % 256;
        carry = (tmp > 0) ? 1 : 0;
        neg[j] = tmp;
    }
    j = REG_SIZE;
    carry = 0;
    while (--j >= 0)
    {
        tmp = prcs->reg[arg.int_value[0] - 1][j] + neg[j] + carry;
        carry = (tmp < 256) ? 0 : 1;
        prcs->reg[arg.int_value[2] - 1][j] = tmp % 256;
    }
    ft_print_op(prcs, prcs->arg, op);
    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
    //ft_update_process(cw, prcs, op);
    prcs->carry = (ft_str_to_int(prcs->reg[arg.int_value[2] - 1], REG_SIZE) == 0) ? 1 : 0;
}

void    ft_fork(t_cw *cw, t_process *prcs, int i, t_op op)
{
    unsigned int    v;
    int             j;

    (void) i;

    v = 0;
    j = -1;
    while (++j < IND_SIZE)
        v = 256 * v + (unsigned char)cw->arena[(prcs->pc + 1 + j) % MEM_SIZE];
    if (!ft_new_process(cw, cw->head, prcs, (prcs->pc + (short int)v % IDX_MOD) % MEM_SIZE))
        return ; //I Have a malloc here
    
    cw->nb_prcs++;
    ft_printf("P%s%u | %s %hd (%d)\n", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name, v, (prcs->pc + (short int)v % IDX_MOD) % MEM_SIZE);
    prcs->pc = (prcs->pc + 1 + IND_SIZE) % MEM_SIZE;
}

void    ft_lfork(t_cw *cw, t_process *prcs, int i, t_op op)
{
    unsigned int    v;
    int             j;

    (void) i;

    v = 0;
    j = -1;
    while (++j < IND_SIZE)
        v = (256 * v + (unsigned char)cw->arena[(prcs->pc + 1 + j) % MEM_SIZE]);
    if (!ft_new_process(cw, cw->head, prcs, (prcs->pc + v) % MEM_SIZE))
        return ; //I Have a malloc here
    cw->nb_prcs++;
    ft_printf("P%s%u | %s %d (%d)\n", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name, v, prcs->pc + v);
    prcs->pc = (prcs->pc + 1 + IND_SIZE) % MEM_SIZE;
}
