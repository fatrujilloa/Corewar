/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:38:28 by ftrujill          #+#    #+#             */
/*   Updated: 2020/02/04 13:41:45 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"


unsigned int    ft_recover_value_arena(t_cw *cw, int pc, int size)
{
    int             i;
    unsigned int    v;

    i = -1;
    v = 0;
    while (++i < size)
       v = (256 * v + (unsigned char)cw->arena[(pc + i) % MEM_SIZE]);
    return (v);
}

void    ft_real_values(t_cw *cw, t_process *prcs, t_arg *arg)
{
    int i;
    int aux;

    aux = 2;
    i = -1;
    while (++i < arg->nb_args && arg->size[i])
    {
        if (arg->type[i] == REG_CODE)
            arg->real_value[i] = ft_str_to_int(prcs->reg[arg->int_value[i] - 1], REG_SIZE);
        else if (arg->type[i] == IND_CODE)
            arg->real_value[i] = ft_recover_value_arena(cw, (prcs->pc + arg->int_value[i]) % MEM_SIZE, REG_SIZE);
        else
            arg->real_value[i] = arg->int_value[i];
        aux += arg->size[i];
    }
}

void    ft_arg_value(t_cw *cw, int pc, t_arg *arg, int i) //If indirect > 4096 (size == IND_SIZE) should be an error ?
{
    int             j;
    unsigned int    v;

    v = 0;
    j = -1;
    while (++j < arg->size[i])
    {
        arg->value[i][j] = (unsigned char)cw->arena[(pc + j) % MEM_SIZE];
        v = 256 * v + arg->value[i][j];
    }
    //arg->int_value[i] = arg->size[i] == IND_SIZE ? v % MEM_SIZE : v;
    arg->int_value[i] = v;
    //ft_printf("arg->int_value[%d] = %d\n", i, arg->int_value[i]);
}

void     ft_arg_values(t_cw *cw, t_process *prcs, t_arg *arg)
{
    int i;
    int aux;

    aux = 2;
    i = -1;
    while (++i < arg->nb_args)
    {
        ft_arg_value(cw, (prcs->pc + aux) % MEM_SIZE, arg, i);
        if (arg->type[i] == REG_CODE && (arg->int_value[i] == 0 ||
            arg->int_value[i] > REG_NUMBER)) //This says that arg is not valid since reg value does not exist
            {
                prcs->valid_arg = -1;
                return ;
            }
        aux = aux + arg->size[i];
    } 
}

int			ft_check_operation(t_process *prcs, t_op op)
{
	t_arg	*arg;

	arg = &prcs->arg;	
	if ((op.opcode == 1) || (op.opcode == 9) || (op.opcode == 12) || (op.opcode == 15))
		return (1);
	if (op.opcode == 2)
		return ((arg->type[0] != DIR_CODE && arg->type[0] != IND_CODE) 
        || arg->type[1] != REG_CODE);
	if (op.opcode == 3)
		return ((arg->type[1] != IND_CODE && arg->type[1] != REG_CODE) 
        || arg->type[0] != REG_CODE);
	if (op.opcode == 4)
		return (arg->type[0] != REG_CODE || arg->type[1] != REG_CODE
        || arg->type[2] != REG_CODE);
	if (op.opcode == 5)
		return (arg->type[0] != REG_CODE || arg->type[1] != REG_CODE
        || arg->type[2] != REG_CODE);
	if (op.opcode == 6 || op.opcode == 7 || op.opcode == 8)
		return (arg->type[2] != REG_CODE);
	if (op.opcode == 10)
		return ((arg->type[1] != REG_CODE && arg->type[1] != DIR_CODE)
        || arg->type[2] != REG_CODE);
	if (op.opcode == 11)
		return ((arg->type[2] != REG_CODE && arg->type[2] != DIR_CODE)
        || arg->type[0] != REG_CODE);
	if (op.opcode == 13)
		return ((arg->type[0] != DIR_CODE && arg->type[0] != IND_CODE) 
        || arg->type[1] != REG_CODE);
	if (op.opcode == 14)
		return ((arg->type[1] != REG_CODE && arg->type[1] != DIR_CODE)
        || arg->type[2] != REG_CODE);
	if (op.opcode == 16)
		return (arg->type[0] != REG_CODE);
	return (0);
}