/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:43:36 by ftrujill          #+#    #+#             */
/*   Updated: 2020/02/04 23:30:56 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void    ft_ld(t_cw *cw, t_process *prcs, int i, t_op op) // DIR | IND, REG
{
    int     j;
    t_arg   arg;
    
    (void)i;
    (void)cw;
    arg = prcs->arg;
    j = -1;
    if (arg.type[0] == IND_CODE)
        while (++j < REG_SIZE)
            prcs->reg[arg.int_value[1] - 1][j] = cw->arena[((prcs->pc + j + (int)arg.int_value[0] % IDX_MOD) % MEM_SIZE + MEM_SIZE) % MEM_SIZE];
    else
        while (++j < DIR_SIZE)
             prcs->reg[arg.int_value[1] - 1][j] = arg.value[0][j];
    ft_printf("P%s%u | %s %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name, arg.type[0] == IND_CODE ?
        ft_recover_value_arena(cw, ((prcs->pc + (int)(arg.int_value[0] % IDX_MOD)) % MEM_SIZE + MEM_SIZE) % MEM_SIZE, REG_SIZE)
        : arg.real_value[0], arg.int_value[1]);

    //ft_printf("P%s%u | %s %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name, arg.real_value[0], arg.int_value[1]);
        //ft_printf("P%s%u | %s %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name, arg.int_value[0], arg.int_value[1]);
       // (arg.type[0] == IND_CODE) ? (int)ft_recover_value_arena(cw, (prcs->pc + j + (arg.int_value[0] % IDX_MOD)) % MEM_SIZE, 4)
       // : (int)arg.real_value[0], arg.int_value[1]);


    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
    //ft_update_process(cw, prcs, op);
    prcs->carry = (arg.real_value[0] == 0) ? 1 : 0;
}

void    ft_lld(t_cw *cw, t_process *prcs, int i, t_op op) // DIR | IND, REG
{
    int     j;
    t_arg   arg;

    (void)i;
    (void)cw;
    arg = prcs->arg;
    j = -1;
    if (arg.type[0] == IND_CODE)
    {
        *(unsigned int*)prcs->reg[arg.int_value[1] - 1] = arg.real_value[0] / 65536;;
        ft_strnrev(prcs->reg[arg.int_value[1] - 1], 4);
        ft_printf("P%s%u | %s %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name, arg.real_value[0] / 65536, arg.int_value[1]);
    }
    else
    {   
        while (++j < DIR_SIZE)
        prcs->reg[arg.int_value[1] - 1][j] = arg.value[0][j];
        ft_printf("P%s%u | %s %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name, arg.real_value[0], arg.int_value[1]);
    }
    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
    //ft_update_process(cw, prcs, op);
    prcs->carry = (arg.real_value[0] == 0) ? 1 : 0;
}

void    ft_ldi(t_cw *cw, t_process *prcs, int i, t_op op) //ARG, DIR | REG, REG
{
    int             j;
    int             address_int;
    unsigned int    address_uint;
    t_arg           arg;
    
    (void)i;
    arg = prcs->arg;
    /*
    address_int = (prcs->pc + ((int)arg.real_value[0] + (int)arg.real_value[1])
        % IDX_MOD) % MEM_SIZE;
    address_uint = (address_int + MEM_SIZE) % MEM_SIZE;
    ft_printf("P%s%u | %s %d %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name, arg.real_value[0], arg.real_value[1], arg.int_value[2]);
    ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", arg.real_value[0], arg.real_value[1], arg.real_value[0]
        + arg.real_value[1], address_int);
    */
    
     address_int = (prcs->pc + ((arg.type[0] == DIR_CODE ? (short int)arg.real_value[0] : (int)arg.real_value[0])
        + (arg.type[1] == DIR_CODE ? (short int)arg.real_value[1] : (int)arg.real_value[1]))
        % IDX_MOD) ;
    address_uint = (address_int % MEM_SIZE + MEM_SIZE) % MEM_SIZE;
    j = -1;
    while (++j < REG_SIZE)
        prcs->reg[arg.int_value[2] - 1][j] = cw->arena[(address_uint + j) % MEM_SIZE];
    ft_printf("P%s%u | %s %d %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name,
    (arg.type[0] == DIR_CODE ? (short int)arg.real_value[0] : (int)arg.real_value[0]),
    (arg.type[1] == DIR_CODE ? (short int)arg.real_value[1] : (int)arg.real_value[1]),
    arg.int_value[2]);
    ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
        (arg.type[0] == DIR_CODE ? (short int)arg.real_value[0] : (int)arg.real_value[0]),
        (arg.type[1] == DIR_CODE ? (short int)arg.real_value[1] : (int)arg.real_value[1]),
        (arg.type[0] == DIR_CODE ? (short int)arg.real_value[0] : (int)arg.real_value[0]) +
        (arg.type[1] == DIR_CODE ? (short int)arg.real_value[1] : (int)arg.real_value[1]), address_int);
    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
}

void    ft_lldi(t_cw *cw, t_process *prcs, int i, t_op op) //ARG, DIR | REG, REG
{
    int             j;
    int             address_int;
    unsigned int    address_uint;
    t_arg           arg;
    
    (void)i;
    arg = prcs->arg;
    address_int = (prcs->pc + (int)arg.real_value[0] + (int)arg.real_value[1])
        % MEM_SIZE;
    address_uint = (address_int + MEM_SIZE) % MEM_SIZE;
    j = -1;
    while (++j < REG_SIZE)
        prcs->reg[arg.int_value[2] - 1][j] = cw->arena[(address_uint + j) % MEM_SIZE];
    ft_printf("P%s%u | %s %d %d r%d\n", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name, arg.real_value[0], arg.real_value[1], arg.int_value[2]);
    ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
        arg.real_value[0], arg.real_value[1], arg.real_value[0]
        + arg.real_value[1], prcs->pc + (int)arg.real_value[0] + (int)arg.real_value[1]);
    prcs->pc = (prcs->pc + arg.total_size) % MEM_SIZE;
    //ft_update_process(cw, prcs, op);
    prcs->carry = (ft_str_to_int(prcs->reg[arg.int_value[2] - 1], REG_SIZE) == 0) ? 1 : 0;
}

