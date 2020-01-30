/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live_st_zjmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:41:02 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/30 22:52:50 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void    ft_live(t_cw *cw, t_process *prcs, int i, t_op op) // DIR
{
    int             j;

    j = -1;
    if (prcs->arg.int_value[0] == ft_str_to_int(prcs->reg[0], 4))
    {
        if (cw->dump_flag == -1)
            ft_printf("un processus dit que le joueur %d(%s) est en vie at "
                    "cycle = %d\n", i, cw->champ[i].name, cw->nb_cycles);
        prcs->alive = 1;
        cw->last_alive = i;
    }
    prcs->pc = (prcs->pc + 1 + DIR_SIZE) % MEM_SIZE;
    ft_update_process(cw, prcs, op);
}

void    ft_st(t_cw *cw, t_process *prcs, int i, t_op op) //REG, IND | REG
{
    int     j;
    t_arg   arg;
    
    arg = prcs->arg;
    j = -1;
    if (arg.type[1] == REG_CODE)
        while (++j < REG_SIZE)
            prcs->reg[arg.int_value[1] - 1][j] = prcs->reg[arg.int_value[0] - 1][j];
    else
        while (++j < REG_SIZE)
            cw->arena[(prcs->pc + j + arg.int_value[1] % IDX_MOD) % MEM_SIZE]
            = prcs->reg[arg.int_value[0] - 1][j];
    ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
    ft_update_process(cw, prcs, op);
}


void    ft_sti(t_cw *cw, t_process *prcs, int i, t_op op) //REG, ARG, DIR | REG
{
    int             j;
    unsigned int    a;
    unsigned int    b;
    unsigned int    s;
    t_arg   arg;
    
    arg = prcs->arg;
    a = (arg.type[1] == REG_CODE) ? ft_str_to_int(prcs->reg[arg.int_value[1] - 1], REG_SIZE) : ft_ind_arg(cw, (prcs->pc + 3) % MEM_SIZE);
    b = (arg.type[2] == REG_CODE) ? ft_str_to_int(prcs->reg[arg.int_value[2] - 1], REG_SIZE) : ft_ind_arg(cw, (prcs->pc + 3 + (arg.size[1] == 1 ? 1 : IND_SIZE) % MEM_SIZE));
    s = (arg.type[1] == IND_CODE) ? 0 : a;
    j = -1;
    if (arg.type[1] == IND_CODE)
        while (++j < IND_SIZE)
            s = (256 * s + (unsigned char)cw->arena[(prcs->pc + j + a % IDX_MOD) % MEM_SIZE]) % IDX_MOD;
    s = (s + b) % IDX_MOD;

   // ft_printf("Arg types = %d, %d, %d, arg_int_values = %u, %u, %u\n", arg.type[0], arg.type[1], arg.type[2], arg.int_value[0], arg.int_value[1], arg.int_value[2]);
    //ft_printf("CURRENT PC = %d, values = %u, %u, Adress to collect info = %u\n", prcs->pc, a, b, prcs->pc + s);

    j = -1;
    while (++j < REG_SIZE)
        cw->arena[(prcs->pc + j + s) % MEM_SIZE] = prcs->reg[arg.int_value[0] - 1][j];
    prcs->pc = (prcs->pc + 2 + 1 + (arg.size[1] == 1 ? 1 : IND_SIZE) + (arg.size[2] == 1 ? 1 : IND_SIZE)) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    ft_update_process(cw, prcs, op);
}

void    ft_zjmp(t_cw *cw, t_process *prcs, int i, t_op op)
{
    int             j;
    unsigned int    v;

    //(void) i;

    v = 0;
    j = -1;
    prcs->pc = (prcs->pc + 1) % MEM_SIZE;
    while (++j < DIR_SIZE)
        v = (256 * v + (unsigned char)cw->arena[(prcs->pc + j) % MEM_SIZE]) % IDX_MOD;
    if (prcs->carry)
        prcs->pc = (prcs->pc + v) % MEM_SIZE;
    else
        prcs->pc = (prcs->pc + DIR_SIZE) % MEM_SIZE; //Or just prcs->pc + 1 ?
    ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    ft_update_process(cw, prcs, op);
}
