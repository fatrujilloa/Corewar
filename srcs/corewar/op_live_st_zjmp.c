/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live_st_zjmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:41:02 by ftrujill          #+#    #+#             */
/*   Updated: 2020/02/03 00:52:51 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void    ft_live(t_cw *cw, t_process *prcs, int i, t_op op) // DIR
{
    int             j;

    (void)i;
    j = -1;
    if (prcs->arg.int_value[0] == ft_str_to_int(prcs->reg[0], 4))
    {
       // if (cw->dump_flag > 0)
            //ft_printf("un processus dit que le joueur %d(%s) est en vie at "
              //      "cycle = %d\n", i, cw->champ[i].name, cw->nb_cycles);
        prcs->alive = 1;
        cw->last_alive = i;
    }
    prcs->pc = (prcs->pc + 1 + DIR_SIZE) % MEM_SIZE;
    ft_print_op(prcs, prcs->arg, op);
}

void    ft_st(t_cw *cw, t_process *prcs, int i, t_op op) //REG, IND | REG
{
    int     j;
    t_arg   arg;
    
        (void)i;
    arg = prcs->arg;
    j = -1;
    if (arg.type[1] == REG_CODE)
        while (++j < REG_SIZE)
            prcs->reg[arg.int_value[1] - 1][j] = prcs->reg[arg.int_value[0] - 1][j];
    else
        while (++j < REG_SIZE)
            cw->arena[(prcs->pc + j + arg.int_value[1] % IDX_MOD) % MEM_SIZE]
            = prcs->reg[arg.int_value[0] - 1][j];
    ft_print_op(prcs, prcs->arg, op);
    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;

}


void    ft_sti(t_cw *cw, t_process *prcs, int i, t_op op) //REG, ARG, DIR | REG
{
    int             j;
    //unsigned int    a;
    //unsigned int    b;
    //unsigned int    s;
    t_arg   arg;
    
        (void)i;
    arg = prcs->arg;
   // ft_printf("\n\nSTARTING sti\n\n");
    //a = (arg.type[1] == REG_CODE) ? ft_str_to_int(prcs->reg[arg.int_value[1] - 1], REG_SIZE) : ft_ind_arg(cw, (prcs->pc + 3) % MEM_SIZE);
    //b = (arg.type[2] == REG_CODE) ? ft_str_to_int(prcs->reg[arg.int_value[2] - 1], REG_SIZE) : ft_ind_arg(cw, (prcs->pc + 3 + (arg.size[1] == 1 ? 1 : IND_SIZE)) % MEM_SIZE);
   // ft_printf("ft_str_to_int(prcs->reg[arg.int_value[2] - 1] = %u, b = %u \n", ft_str_to_int(prcs->reg[arg.int_value[2] - 1], REG_SIZE), b);
    //ft_printf("%u, %u\n", arg.int_value[2] - 1, ft_str_to_int(prcs->reg[9], REG_SIZE) );
    //ft_printf("%u, %u\n", arg.int_value[2] - 1, ft_str_to_int(prcs->reg[arg.int_value[2] - 1], REG_SIZE) );
    //s = (arg.type[1] == IND_CODE) ? 0 : a;

/*
    ft_printf("\n s = %u\n", s);
    ft_printf("Value in reg 10 = %u, arg_type = %d, REG_CODE = %d\n", ft_str_to_int(prcs->reg[9], REG_SIZE), arg.type[2], REG_CODE);;
    ft_printf("a = %u, b = %u\n", a, b);
    ft_printf("Arg types = %d, %d, %d, arg_int_values = %u, %u, %u\n", arg.type[0], arg.type[1], arg.type[2], arg.int_value[0], arg.int_value[1], arg.int_value[2]);
    ft_printf("CURRENT PC = %d, values = %u, %u, Adress to collect info = %u\n", prcs->pc, a, b, prcs->pc + s);
    ft_printf("Value of REG = %u\n", ft_str_to_int(prcs->reg[arg.int_value[0] - 1], REG_SIZE));
    j = -1;
    while(++j < REG_SIZE)
        ft_printf("prcs->reg[arg.int_value[0] - 1][%d] = %u\n", j, prcs->reg[arg.int_value[0] - 1][j]);
*/
    j = -1;
    while (++j < REG_SIZE)
        cw->arena[(prcs->pc + j + arg.real_value[1] % IDX_MOD + ft_str_to_int(prcs->reg[prcs->arg.int_value[2] - 1], REG_SIZE)) % MEM_SIZE] =
            prcs->reg[arg.int_value[0] - 1][j];

    ft_print_op(prcs, prcs->arg, op);
    //ft_printf("Le joueur %d(%s) a executé %s at cycle = %d\n", i, cw->champ[i].name, op.name, cw->nb_cycles);
    prcs->pc = (prcs->pc + 2 + 1 + (arg.size[1] == 1 ? 1 : IND_SIZE) + (arg.size[2] == 1 ? 1 : IND_SIZE)) % MEM_SIZE;
    ft_update_process(cw, prcs, op);
}

void    ft_zjmp(t_cw *cw, t_process *prcs, int i, t_op op) //NEED TO BE CHECKED
{
    int             j;
    unsigned int    v;

    (void)i;

    v = 0;
    j = -1;
    while (++j < IND_SIZE)
        v = (256 * v + (unsigned char)cw->arena[(prcs->pc + 1 + j) % MEM_SIZE]);
    if (prcs->carry)
    {
        ft_printf("P   %u | %s %d OK\n", prcs->nb + 1, op.name, v);
        prcs->pc = (prcs->pc + v % IDX_MOD) % MEM_SIZE;
    }
    else
    {
        ft_printf("P   %u | %s %d FAIlED\n", prcs->nb + 1, op.name, v);
        prcs->pc = (prcs->pc + 1 + IND_SIZE) % MEM_SIZE;
    }
    ft_update_process(cw, prcs, op);
}
