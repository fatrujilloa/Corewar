/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti_fork_lld_lldi_lfork.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:43:36 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/30 22:49:54 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"


void    ft_ld(t_cw *cw, t_process *prcs, int i, t_op op) // DIR | IND, REG
{
    int     j;
    t_arg   arg;
    
    arg = prcs->arg;
    j = -1;
    if (arg.type[0] == IND_CODE)
        while (++j < REG_SIZE)
            prcs->reg[arg.int_value[1] - 1][j] = cw->arena[(prcs->pc + j + arg.int_value[0] % IDX_MOD) % MEM_SIZE];
    else
        while (++j < DIR_SIZE)
             prcs->reg[arg.int_value[1] - 1][j] = arg.value[0][j];
    ft_printf("Le joueur %d(%s) a executé %s and the value in register %d is %uat cycle = %d \n", i, cw->champ[i].name, op.name, arg.int_value[1], ft_str_to_int(prcs->reg[arg.int_value[1] - 1], REG_SIZE), cw->nb_cycles);
    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
    //ft_printf("P    %d |    %s %u\n", i, op.name, ft_str_to_int(prcs->reg[arg.int_value[1] - 1], REG_SIZE));
    ft_update_process(cw, prcs, op);
}


void    ft_ldi(t_cw *cw, t_process *prcs, int i, t_op op) //ARG, DIR | REG, REG // Done following instructions from ˜Sujet epitech"
{
    int             j;
    unsigned int    a;
    unsigned int    b;
    unsigned int    s;
    t_arg   arg;
    
    arg = prcs->arg;
    a = (arg.type[0] == REG_CODE) ? ft_str_to_int(prcs->reg[arg.int_value[0] - 1], REG_SIZE) : ft_ind_arg(cw, (prcs->pc + 2) % MEM_SIZE);
    b = (arg.type[1] == REG_CODE) ? ft_str_to_int(prcs->reg[arg.int_value[1] - 1], REG_SIZE) : ft_ind_arg(cw, (prcs->pc + 2 + (arg.size[0] == 1 ? 1 : IND_SIZE)) % MEM_SIZE);
    arg.int_value[2] = (unsigned char)cw->arena[(prcs->pc + 2 + (arg.size[0] == 1 ? 1 : IND_SIZE) + (arg.size[1] == 1 ? 1 : IND_SIZE)) % MEM_SIZE];
    s = (arg.type[0] == IND_CODE) ? 0 : a;
    j = -1;
    if (arg.type[0] == IND_CODE)
        while (++j < IND_SIZE)
            s = (256 * s + (unsigned char)cw->arena[(prcs->pc + j + a % IDX_MOD) % MEM_SIZE]) % IDX_MOD;
    s = (s + b) % IDX_MOD;

    //ft_printf("ldi | Arg types = %d, %d, %d, arg_int_values = %u, %u, %u\n", arg.type[0], arg.type[1], arg.type[2], arg.int_value[0], arg.int_value[1], arg.int_value[2]);
    //ft_printf("ldi | CURRENT PC = %d, values = %u, %u, Adress to collect info = %u\n", prcs->pc, a, b, prcs->pc + s);

    //ft_printf("CURRENT PC = %d, values = %u, %u, Adress to collect info = %u\n", prcs->pc, a, b, prcs->pc + s);

    j = -1;
    while (++j < REG_SIZE)
    {
        prcs->reg[arg.int_value[2] - 1][j] = (unsigned char)cw->arena
            [(prcs->pc + j + s) % MEM_SIZE];
        //ft_printf("ldi | reg[%d][%d] = %u\n", arg.int_value[2] - 1, j, prcs->reg[arg.int_value[2] - 1][j]);
    }
    prcs->pc = (prcs->pc + 2 + (arg.size[0] == 1 ? 1 : IND_SIZE) + (arg.size[1] == 1 ? 1 : IND_SIZE) + 1) % MEM_SIZE;
    ft_printf("ldi | Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    ft_update_process(cw, prcs, op);
}

void    ft_lld(t_cw *cw, t_process *prcs, int i, t_op op) // DIR | IND, REG
{
    int     j;
    t_arg   arg;
    
    arg = prcs->arg;
    j = -1;
    if (arg.type[0] == IND_CODE)
        while (++j < REG_SIZE)
            prcs->reg[arg.int_value[1] - 1][j] = cw->arena[(prcs->pc + j + arg.int_value[0]) % MEM_SIZE];
    else
        while (++j < DIR_SIZE)
             prcs->reg[arg.int_value[1] - 1][j] = arg.value[0][j];
    //ft_printf("Le joueur %d(%s) a executé %s and the value in register %d is %u\n",
       // i, cw->champ[i].name, op.name, arg.int_value[1], ft_str_to_int(prcs->reg[arg.int_value[1] - 1], REG_SIZE));
    prcs->pc = (prcs->pc + 2 + arg.size[0] + 1) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    ft_update_process(cw, prcs, op);
}

void    ft_lldi(t_cw *cw, t_process *prcs, int i, t_op op) //ARG, DIR | REG, REG
{
    int             j;
    unsigned int    a;
    unsigned int    b;
    unsigned int    s;
    t_arg   arg;
    
    arg = prcs->arg;
    a = (arg.type[0] == REG_CODE) ? ft_str_to_int(prcs->reg[arg.int_value[0] - 1], REG_SIZE) : ft_ind_arg(cw, prcs->pc + 2);
    b = (arg.type[1] == REG_CODE) ? ft_str_to_int(prcs->reg[arg.int_value[1] - 1], REG_SIZE) : ft_ind_arg(cw, prcs->pc + 2 + (arg.size[0] == 1 ? 1 : IND_SIZE));
    arg.int_value[2] = (unsigned char)cw->arena[(prcs->pc + 2 + (arg.size[0] == 1 ? 1 : IND_SIZE) + (arg.size[1] == 1 ? 1 : IND_SIZE)) % MEM_SIZE];
    s = (arg.type[0] == IND_CODE) ? 0 : a;
    j = -1;
    if (arg.type[0] == IND_CODE)
        while (++j < IND_SIZE)
            s = (256 * s + (unsigned char)cw->arena[(prcs->pc + j + a) % MEM_SIZE]);
    s = s + b;
    j = -1;
    while (++j < REG_SIZE)
    {
        prcs->reg[arg.int_value[2] - 1][j] = (unsigned char)cw->arena
            [(prcs->pc + j + s) % MEM_SIZE];
        //ft_printf("reg[%d][%d] = %u\n", arg.int_value[2] - 1, j, prcs->reg[arg.int_value[2] - 1][j]);
    }
    prcs->pc = (prcs->pc + 2 + (arg.size[0] == 1 ? 1 : IND_SIZE) + (arg.size[1] == 1 ? 1 : IND_SIZE) + 1) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    ft_update_process(cw, prcs, op);
}

