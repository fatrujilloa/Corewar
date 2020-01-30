/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:35:04 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/30 22:39:32 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void    ft_arg_size(t_process *prcs, t_arg *arg)
{
    int i;

    i = -1;
    while (++i < arg->nb_args)
    {
        if (arg->type[i] == REG_CODE)
            arg->size[i] = 1;
        else if (arg->type[i] == DIR_CODE)
            arg->size[i] = DIR_SIZE;
        else if (arg->type[i] == IND_CODE)
            arg->size[i] = IND_SIZE;
        else
        {
            arg->size[i] = 0;
            prcs->valid_arg = 0;
        //ft_printf("arg->size[%d] = %u\n", i, arg->size[i]);
        }
        arg->total_size += arg->size[i];
    }
    arg->total_size += 2;
}

void    ft_init_arg(t_arg *arg, unsigned char nb_args)
{
    int i;

    arg->total_size = 0;
    ft_bzero(arg->type, MAX_ARGS_NUMBER);
    ft_bzero(arg->size, MAX_ARGS_NUMBER);
    ft_bzero(arg->int_value, MAX_ARGS_NUMBER);
    i = -1;
    while (++i < MAX_ARGS_NUMBER)
        ft_bzero(arg->value[i], MAX_SIZE);
    arg->nb_args = nb_args;
}

void    ft_get_args(t_cw *cw, t_process *prcs, t_arg *arg, t_op op)
{
    unsigned int    a;
    unsigned int    b;
    int             i;
    unsigned char   byte;

    prcs->valid_arg = 1;
    ft_init_arg(arg, op.nb_arg);
    if (op.opcode == 1 || op.opcode == 9 || op.opcode == 12 || op.opcode == 15)
    {
        a = 0;
        i = -1;
        while (++i < DIR_SIZE)
            a = 256 * a + (unsigned char)cw->arena[(prcs->pc + 1 + i) % MEM_SIZE];
        arg->int_value[0] = a;
        return ;
    }
    byte = (unsigned char)cw->arena[(prcs->pc + 1) % MEM_SIZE];
    a = 128;
    b = 64;
    i = -1;
    while (i++ < arg->nb_args)
    {
        arg->type[i] = ((a + b) & byte) >> (6 - 2 * i);
        a = a / 4;
        b = b / 4;
    }
    i = -1;
    ft_arg_size(prcs, arg);
    if (prcs->valid_arg == 1)
        ft_arg_values(cw, prcs, arg);
    if (prcs->valid_arg == 1 && ft_check_operation(prcs, op))
        prcs->valid_arg = -2;
}