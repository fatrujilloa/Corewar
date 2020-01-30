/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:41:49 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/30 22:56:18 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void    ft_aff(t_cw *cw, t_process *prcs, int i, t_op op) // REG
{
    t_arg   arg;
    
    arg = prcs->arg;
    
    //int j = -1;
    //while (++j < REG_SIZE)
    //  ft_printf("reg[%d][%d] = %u\n", arg.int_value[0] - 1, j, prcs->reg[arg.int_value[0] - 1][j]);
    
    ft_printf("%u\n", ft_str_to_int(prcs->reg[arg.int_value[0] - 1], REG_SIZE));

    prcs->pc = (prcs->pc + 3) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    ft_update_process(cw, prcs, op);
}

void    ft_and(t_cw *cw, t_process *prcs, int i, t_op op) //ARG, ARG, REG
{
    int             j;
    unsigned char   a[MAX_SIZE];
    unsigned char   b[MAX_SIZE];
    t_arg   arg;
    
    arg = prcs->arg;
    j = -1;
    while (++j < DIR_SIZE)
    {
        a[j] = arg.value[0][j];
        if (arg.type[0] == REG_CODE)
            a[j] = prcs->reg[arg.int_value[0] - 1][j];
        else if (arg.type[0] == IND_CODE)
            a[j] = cw->arena[(prcs->pc + arg.int_value[0] % IDX_MOD) % MEM_SIZE];
        b[j] = arg.value[1][j];
        if (arg.type[1] == REG_CODE)
            b[j] = prcs->reg[arg.int_value[1] - 1][j];
        else if (arg.type[1] == IND_CODE)
            b[j] = cw->arena[(prcs->pc + arg.int_value[1] % IDX_MOD) % MEM_SIZE];
        prcs->reg[arg.int_value[2] - 1][j] = a[j] & b[j];
    }

   /* j = -1;
    while (++j < DIR_SIZE)
        ft_printf("a[%d] = %u, b[%d] = %u, c[%d] = %u\n", j, a[j], j, b[j], j, prcs->reg[arg.int_value[2] - 1][j]);
    */
   
    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    ft_update_process(cw, prcs, op);
}

void    ft_or(t_cw *cw, t_process *prcs, int i, t_op op) //ARG, ARG, REG
{
    int             j;
    unsigned char   a[MAX_SIZE];
    unsigned char   b[MAX_SIZE];
    t_arg   arg;
    
    arg = prcs->arg;
    j = -1;
    while (++j < DIR_SIZE)
    {
        a[j] = arg.value[0][j];
        if (arg.type[0] == REG_CODE)
            a[j] = prcs->reg[arg.int_value[0] - 1][j];
        else if (arg.type[0] == IND_CODE)
            a[j] = cw->arena[(prcs->pc + arg.int_value[0] % IDX_MOD) % MEM_SIZE];
        b[j] = arg.value[1][j];
        if (arg.type[1] == REG_CODE)
            b[j] = prcs->reg[arg.int_value[1] - 1][j];
        else if (arg.type[1] == IND_CODE)
            b[j] = cw->arena[(prcs->pc + arg.int_value[1] % IDX_MOD) % MEM_SIZE];
        prcs->reg[arg.int_value[2] - 1][j] = a[j] | b[j];
    }
/*
    j = -1;
    while (++j < DIR_SIZE)
        ft_printf("a[%d] = %u, b[%d] = %u, c[%d] = %u\n", j, a[j], j, b[j], j, prcs->reg[arg.int_value[2] - 1][j]);
*/
    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
   ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    ft_update_process(cw, prcs, op);
}

void    ft_xor(t_cw *cw, t_process *prcs, int i, t_op op) //ARG, ARG, REG
{
    int             j;
    unsigned char   a[MAX_SIZE];
    unsigned char   b[MAX_SIZE];
    t_arg   arg;
    
    arg = prcs->arg;
    j = -1;
    while (++j < DIR_SIZE)
    {
        a[j] = arg.value[0][j];
        if (arg.type[0] == REG_CODE)
            a[j] = prcs->reg[arg.int_value[0] - 1][j];
        else if (arg.type[0] == IND_CODE)
            a[j] = cw->arena[(prcs->pc + arg.int_value[0] % IDX_MOD) % MEM_SIZE];
        b[j] = arg.value[1][j];
        if (arg.type[1] == REG_CODE)
            b[j] = prcs->reg[arg.int_value[1] - 1][j];
        else if (arg.type[1] == IND_CODE)
            b[j] = cw->arena[(prcs->pc + arg.int_value[1] % IDX_MOD) % MEM_SIZE];
        prcs->reg[arg.int_value[2] - 1][j] = a[j] ^ b[j];
    }
/*
    j = -1;
    while (++j < DIR_SIZE)
        ft_printf("a[%d] = %u, b[%d] = %u, c[%d] = %u\n", j, a[j], j, b[j], j, prcs->reg[arg.int_value[2] - 1][j]);
*/
    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    ft_update_process(cw, prcs, op);
}

