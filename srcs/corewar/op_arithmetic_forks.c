/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arithmetic_forks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:50:25 by ftrujill          #+#    #+#             */
/*   Updated: 2020/02/04 18:47:47 by ftrujill         ###   ########.fr       */
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
    int             int_address;
    unsigned int    uint_address;
    t_arg   arg;

    (void)i;
    arg = prcs->arg;
    int_address = (prcs->pc + (short int)arg.int_value[0] % IDX_MOD) % MEM_SIZE;
    uint_address =  (int_address + MEM_SIZE) % MEM_SIZE;
    cw->nb_prcs++;
    ft_new_process(cw, cw->head, prcs, uint_address);
    ft_printf("P%s%u | %s %d (%d)\n", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name,
    (short int)arg.int_value[0], int_address);
    prcs->pc = (prcs->pc + 1 + IND_SIZE) % MEM_SIZE;
}

void    ft_lfork(t_cw *cw, t_process *prcs, int i, t_op op)
{
    int             int_address;
    unsigned int    uint_address;
    t_arg   arg;

    (void) i;
    arg = prcs->arg;
    int_address = (prcs->pc + (short int)arg.int_value[0]);
    uint_address = (int_address % MEM_SIZE + MEM_SIZE) % MEM_SIZE;
    cw->nb_prcs++;
    ft_new_process(cw, cw->head, prcs, uint_address);
    ft_printf("P%s%u | %s %d (%d)\n", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name,
    (short int)arg.int_value[0], int_address);
    prcs->pc = (prcs->pc + 1 + IND_SIZE) % MEM_SIZE;
}
