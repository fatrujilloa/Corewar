/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:35:04 by ftrujill          #+#    #+#             */
/*   Updated: 2020/02/04 18:40:33 by ftrujill         ###   ########.fr       */
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
    ft_bzero(arg->real_value, MAX_ARGS_NUMBER);
    i = -1;
    while (++i < MAX_ARGS_NUMBER)
        ft_bzero(arg->value[i], MAX_SIZE);
    arg->nb_args = nb_args;
}

void    ft_get_args(t_cw *cw, t_process *prcs, t_arg *arg, t_op op)
{
    unsigned int    a;
    int             b;
    int             i;
    unsigned char   byte;

    prcs->valid_arg = 1;
    ft_init_arg(arg, op.nb_arg);
    if (op.opcode == 1 || op.opcode == 9 || op.opcode == 12 || op.opcode == 15)
    {
        a = 0;
        b = (op.opcode == 1 ? DIR_SIZE : IND_SIZE);
        i = -1;
        while (++i < b)
        {
            a = 256 * a + (unsigned char)cw->arena[(prcs->pc + 1 + i) % MEM_SIZE];
        }
        arg->int_value[0] = a;
        arg->total_size = 1 + b;
        return ;
    }
    byte = (unsigned char)cw->arena[(prcs->pc + 1) % MEM_SIZE];
    a = 128;
    b = 64;
    i = -1;
    //ft_printf("BYTE = %d\n",  byte);
    while (++i < arg->nb_args)
    {
        arg->type[i] = ((a + b) & byte) >> (6 - 2 * i);
        a = a / 4;
        b = b / 4;
    }
    ft_arg_size(prcs, arg);
    if (op.opcode == 10 || op.opcode == 11 || op.opcode == 14)
    {
        i = -1;
        while (++i < arg->nb_args)
            arg->size[i] = (arg->type[i] == DIR_CODE) ? IND_SIZE : arg->size[i];
        arg->total_size = 2 + arg->size[0] + arg->size[1] + arg->size[2];
    }
    /*ft_printf("\n ARG TYPES: \n");
    i = -1;
    while(++i < arg->nb_args)
        ft_printf("arg->type[%d] = %d, arg->size[%d] = %d\n", i, arg->type[i], i, arg->size[i]);
    */
    if (prcs->valid_arg == 1)
        ft_arg_values(cw, prcs, arg);
    if (prcs->valid_arg == 1)
        ft_real_values(cw, prcs, arg);
    if (prcs->valid_arg == 1 && ft_check_operation(prcs, op))
        prcs->valid_arg = -2;
    //ft_printf(" prcs->valid_arg for op = %s is equal to %d\n", op.name,  prcs->valid_arg);
}