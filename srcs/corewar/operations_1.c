/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 22:52:26 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/28 01:42:53 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
void    ft_strnrev(unsigned char *str, unsigned int size)
{
    unsigned int    i;
    char            tmp;

    i = 0;
    while (i < size / 2)
    {
        tmp = str[i];
        str[i] = str[size - 1 - i];
        str[size - 1 - i] = tmp;
        i++;
    }
}
*/

int     ft_new_prcs(t_process **lst, int new_pc)
{
	int			j;
	t_process	*process;
	t_process	*new_process;

	process = *lst;
	while (process->next)
		process = process->next;
	if (!(process->next = (t_process*)ft_memalloc(sizeof(t_process))))
        return (0);
	new_process = process->next;
	new_process->pc = new_pc;
	new_process->carry = process->carry;
	new_process->wait_until = process->wait_until;
	new_process->alive = 0;
	process->next = NULL;
	j = -1;
	while (++j < REG_NUMBER)
		ft_bzero(process->reg[j], REG_SIZE);
    return (1);
}

void    ft_update_process(t_cw *cw, t_process *prcs, t_op op)
{
    prcs->carry = op.carry ? op.carry : prcs->carry;
    prcs->wait_until = cw->nb_cycles + op.cycle;
    prcs = prcs->next;
}

unsigned int    ft_str_to_int(unsigned char *str, unsigned int size)
{
    unsigned int    i;
    unsigned int    v;

    v = 0;
    i = 0;
    while (i < size)
        v = 256 * v + str[i++];
    return (v);
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
    arg->int_value[i] = v;
}

int     ft_arg_values(t_cw *cw, t_process *prcs, t_arg *arg)
{
    int i;
    int aux;

    aux = 1;
    i = -1;
    while (++i < arg->nb_args && arg->size[i])
    {
        ft_arg_value(cw, (prcs->pc + aux) % MEM_SIZE, arg, i);
        //ft_printf("arg->type[%d] = %u, arg->int_value[%d] = %u\n", i, arg->type[i], i, arg->int_value[i]);
        if (arg->type[i] == REG_CODE
            && (arg->int_value[i] == 0 || arg->int_value[i] > REG_NUMBER))
            return (0);
        aux = aux + arg->size[i];
    }
    prcs->pc = (prcs->pc - 1) % MEM_SIZE;
    return (1);
}

int     ft_arg_size(t_arg *arg)
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
            return (0);
        }
        //ft_printf("arg->size[%d] = %u\n", i, arg->size[i]);
    }
    return (1);
}

int     ft_encoding_byte(t_cw *cw, t_process *prcs, t_arg *arg)
{
    int             i;
    int             a;
    int             b;
    unsigned char   byte;

    prcs->pc = (prcs->pc + 1) % MEM_SIZE;
    byte = (unsigned char)cw->arena[prcs->pc];
    i = -1;
    a = 128;
    b = 64;
    while (i++ < arg->nb_args)
    {
        arg->type[i] = ((a + b) & byte) >> (6 - 2 * i);
        a = a / 4;
        b = b / 4;
    }
    i = -1;
    return (ft_arg_size(arg) && ft_arg_values(cw, prcs, arg)); 
}

void    ft_live(t_cw *cw, t_process *prcs, int i, t_op op) // DIR
{
    int             j;
    unsigned int    v;

    v = 0;
    j = -1;
    prcs->pc = (prcs->pc + 1) % MEM_SIZE;
    while (++j < DIR_SIZE)
        v = 256 * v + (unsigned char)cw->arena[(prcs->pc + j) % MEM_SIZE];
    prcs->alive = 1;
    cw->last_alive = i;
    prcs->pc = (prcs->pc + DIR_SIZE) % MEM_SIZE;
    ft_printf("un processus dit que le joueur %d(%s) est en vie\n",
        i, cw->champ[i].name);
    //ft_printf("P    %d |    %s %u\n", i, op.name, v);
    ft_update_process(cw, prcs, op);
}

void    ft_ld(t_cw *cw, t_process *prcs, int i, t_op op) // DIR | IND, REG
{
    t_arg   arg;
    int     j;

    arg.nb_args = 2;
    if (!ft_encoding_byte(cw, prcs, &arg)
        || (arg.type[0] != DIR_CODE && arg.type[0] != IND_CODE) 
        || arg.type[1] != REG_CODE)
        return ;
    j = -1;
    if (arg.type[0] == IND_CODE)
        while (++j < REG_SIZE)
            prcs->reg[arg.int_value[1] - 1][j] = cw->arena[(prcs->pc + j + arg.int_value[0] % IDX_MOD) % MEM_SIZE];
    else
        while (++j < DIR_SIZE)
             prcs->reg[arg.int_value[1] - 1][j] = arg.value[0][j];
    ft_printf("Le joueur %d(%s) a executé %s and the value in register %d is %u\n", i, cw->champ[i].name, op.name, arg.int_value[1], ft_str_to_int(prcs->reg[arg.int_value[1] - 1], REG_SIZE));
    prcs->pc = (prcs->pc + 2 + arg.size[0] + 1) % MEM_SIZE;
    //ft_printf("P    %d |    %s %u\n", i, op.name, ft_str_to_int(prcs->reg[arg.int_value[1] - 1], REG_SIZE));
    ft_update_process(cw, prcs, op);
}

void    ft_st(t_cw *cw, t_process *prcs, int i, t_op op) //REG, IND | REG
{
    t_arg   arg;
    int     j;

    arg.nb_args = 2;
    if (!ft_encoding_byte(cw, prcs, &arg)
        || (arg.type[1] != IND_CODE && arg.type[1] != REG_CODE) 
        || arg.type[0] != REG_CODE)
        return ;
    j = -1;
    if (arg.type[1] == REG_CODE)
        while (++j < REG_SIZE)
            prcs->reg[arg.int_value[1] - 1][j] = prcs->reg[arg.int_value[0] - 1][j];
    else
        while (++j < REG_SIZE)
            cw->arena[(prcs->pc + j + arg.int_value[1] % IDX_MOD) % MEM_SIZE]
            = prcs->reg[arg.int_value[0] - 1][j];
    ft_printf("Le joueur %d(%s) a executé %s\n", i, cw->champ[i].name, op.name);
    prcs->pc = (prcs->pc + 2 + 1 + arg.size[1]) % MEM_SIZE;
    ft_update_process(cw, prcs, op);
}

void    ft_add(t_cw *cw, t_process *prcs, int i, t_op op) //    3 REG
{
    t_arg           arg;
    int             j;
    int             carry;
    int             tmp;

    arg.nb_args = 3;
    if (!ft_encoding_byte(cw, prcs, &arg)
        || arg.type[0] != REG_CODE || arg.type[1] != REG_CODE
        || arg.type[2] != REG_CODE)
        return ;
    j = REG_SIZE;
    carry = 0;
    while (--j >= 0)
    {
        tmp = prcs->reg[arg.int_value[0] - 1][j]
            + prcs->reg[arg.int_value[1] - 1][j] + carry;
        carry = (tmp < 256) ? 0 : 1;
        prcs->reg[arg.int_value[2] - 1][j] = tmp % 256;
    }
    prcs->pc = (prcs->pc + 2 + 3) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s\n", i, cw->champ[i].name, op.name);
    ft_update_process(cw, prcs, op);
}

void    ft_sub(t_cw *cw, t_process *prcs, int i, t_op op) // 3 REG
{
    t_arg           arg;
    int             j;
    int             carry;
    int             tmp;
    unsigned char   neg[REG_SIZE];

    arg.nb_args = 3;
    if (!ft_encoding_byte(cw, prcs, &arg)
        || arg.type[0] != REG_CODE || arg.type[1] != REG_CODE
        || arg.type[2] != REG_CODE)
        return ;
    j = REG_SIZE;
    carry = 0;
    while (--j >= 0)
    {
        tmp = (256 - prcs->reg[arg.int_value[1] - 1][j] - carry) % 256;
        //ft_printf("prcs->reg[arg.int_value[1] - 1][%d] = %u, tmp = %d\n", j, prcs->reg[arg.int_value[1] - 1][j], tmp);
        carry = (tmp > 0) ? 1 : 0;
        neg[j] = tmp;
    }
    j = REG_SIZE;
    carry = 0;
    while (--j >= 0)
    {
        //ft_printf("neg[%d] = %u\n", j, neg[j]);
        tmp = prcs->reg[arg.int_value[0] - 1][j] + neg[j] + carry;
        carry = (tmp < 256) ? 0 : 1;
        prcs->reg[arg.int_value[2] - 1][j] = tmp % 256;
    }
    prcs->pc = (prcs->pc + 2 + 3) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s\n", i, cw->champ[i].name, op.name);
    ft_update_process(cw, prcs, op);
}

void    ft_and(t_cw *cw, t_process *prcs, int i, t_op op) //ARG, ARG, REG
{
    t_arg           arg;
    int             j;
    unsigned char   a[MAX_SIZE];
    unsigned char   b[MAX_SIZE];

    arg.nb_args = 3;
    if (!ft_encoding_byte(cw, prcs, &arg) || arg.type[2] != REG_CODE)
        return ;
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
    prcs->pc = (prcs->pc + 2 + arg.size[0] + arg.size[1] + 1) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s\n", i, cw->champ[i].name, op.name);
    ft_update_process(cw, prcs, op);
}

void    ft_or(t_cw *cw, t_process *prcs, int i, t_op op) //ARG, ARG, REG
{
    t_arg           arg;
    int             j;
    unsigned char   a[MAX_SIZE];
    unsigned char   b[MAX_SIZE];

    arg.nb_args = 3;
    if (!ft_encoding_byte(cw, prcs, &arg) || arg.type[2] != REG_CODE)
        return ;
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
    prcs->pc = (prcs->pc + 2 + arg.size[0] + arg.size[1] + 1) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s\n", i, cw->champ[i].name, op.name);
    ft_update_process(cw, prcs, op);
}

void    ft_xor(t_cw *cw, t_process *prcs, int i, t_op op) //ARG, ARG, REG
{
    t_arg           arg;
    int             j;
    unsigned char   a[MAX_SIZE];
    unsigned char   b[MAX_SIZE];

    arg.nb_args = 3;
    if (!ft_encoding_byte(cw, prcs, &arg) || arg.type[2] != REG_CODE)
        return ;
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
    prcs->pc = (prcs->pc + 2 + arg.size[0] + arg.size[1] + 1) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s\n", i, cw->champ[i].name, op.name);
    ft_update_process(cw, prcs, op);
}

void    ft_zjmp(t_cw *cw, t_process *prcs, int i, t_op op)
{
    int             j;
    unsigned int    v;

    v = 0;
    j = -1;
    prcs->pc = (prcs->pc + 1) % MEM_SIZE;
    while (++j < DIR_SIZE)
        v = (256 * v + (unsigned char)cw->arena[(prcs->pc + j) % MEM_SIZE]) % IDX_MOD;
    if (prcs->carry)
        prcs->pc = (prcs->pc + v) % MEM_SIZE;
    else
        prcs->pc = (prcs->pc + DIR_SIZE) % MEM_SIZE; //Or just prcs->pc + 1 ?
    ft_printf("Le joueur %d(%s) a executé %s\n", i, cw->champ[i].name, op.name);
    ft_update_process(cw, prcs, op);
}

unsigned int    ft_ind_arg(t_cw *cw, int pc)
{
    int             i;
    unsigned int    v;

    i = -1;
    v = 0;
    while (++i < IND_SIZE)
        v = (256 * v + (unsigned char)cw->arena[(pc + i) % MEM_SIZE]) % MEM_SIZE;
    return (v);
}

void    ft_ldi(t_cw *cw, t_process *prcs, int i, t_op op) //ARG, DIR | REG, REG // Done following instructions from ˜Sujet epitech"
{
    t_arg           arg;
    int             j;
    unsigned int    a;
    unsigned int    b;
    unsigned int    s;

    arg.nb_args = 3;
    if (!ft_encoding_byte(cw, prcs, &arg)
        || (arg.type[1] != REG_CODE && arg.type[1] != DIR_CODE)
        || arg.type[2] != REG_CODE)
        return ;
    a = (arg.type[0] == REG_CODE) ? ft_str_to_int(prcs->reg[arg.int_value[0] - 1], REG_SIZE) : ft_ind_arg(cw, prcs->pc + 2);
    b = (arg.type[1] == REG_CODE) ? ft_str_to_int(prcs->reg[arg.int_value[1] - 1], REG_SIZE) : ft_ind_arg(cw, prcs->pc + 2 + (arg.size[0] == 1 ? 1 : IND_SIZE));
    arg.int_value[2] = (unsigned char)cw->arena[(prcs->pc + 2 + (arg.size[0] == 1 ? 1 : IND_SIZE) + (arg.size[1] == 1 ? 1 : IND_SIZE)) % MEM_SIZE];
    s = (arg.type[0] == IND_CODE) ? 0 : a;
    j = -1;
    if (arg.type[0] == IND_CODE)
        while (++j < IND_SIZE)
            s = (256 * s + (unsigned char)cw->arena[(prcs->pc + j + a % IDX_MOD) % MEM_SIZE]) % IDX_MOD;
    s = (s + b) % IDX_MOD;

    //ft_printf("CURRENT PC = %d, values = %u, %u, Adress to collect info = %u\n", prcs->pc, a, b, prcs->pc + s);

    j = -1;
    while (++j < REG_SIZE)
    {
        prcs->reg[arg.int_value[2] - 1][j] = (unsigned char)cw->arena
            [(prcs->pc + j + s) % MEM_SIZE];
        //qft_printf("reg[%d][%d] = %u\n", arg.int_value[2] - 1, j, prcs->reg[arg.int_value[2] - 1][j]);
    }
    prcs->pc = (prcs->pc + 2 + (arg.size[0] == 1 ? 1 : IND_SIZE) + (arg.size[1] == 1 ? 1 : IND_SIZE) + 1) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s\n", i, cw->champ[i].name, op.name);
    ft_update_process(cw, prcs, op);
}

void    ft_sti(t_cw *cw, t_process *prcs, int i, t_op op) //REG, ARG, DIR | REG
{
    t_arg           arg;
    int             j;
    unsigned int    a;
    unsigned int    b;
    unsigned int    s;

    arg.nb_args = 3;
    if (!ft_encoding_byte(cw, prcs, &arg)
        || (arg.type[2] != REG_CODE && arg.type[2] != DIR_CODE)
        || arg.type[0] != REG_CODE)
        return ;
    a = (arg.type[1] == REG_CODE) ? ft_str_to_int(prcs->reg[arg.int_value[1] - 1], REG_SIZE) : ft_ind_arg(cw, prcs->pc + 3);
    b = (arg.type[2] == REG_CODE) ? ft_str_to_int(prcs->reg[arg.int_value[2] - 1], REG_SIZE) : ft_ind_arg(cw, prcs->pc + 3 + (arg.size[1] == 1 ? 1 : IND_SIZE));
    s = (arg.type[1] == IND_CODE) ? 0 : a;
    j = -1;
    if (arg.type[1] == IND_CODE)
        while (++j < IND_SIZE)
            s = (256 * s + (unsigned char)cw->arena[(prcs->pc + j + a % IDX_MOD) % MEM_SIZE]) % IDX_MOD;
    s = (s + b) % IDX_MOD;

   // ft_printf("CURRENT PC = %d, values = %u, %u, Adress to collect info = %u\n", prcs->pc, a, b, prcs->pc + s);

    j = -1;
    while (++j < REG_SIZE)
        cw->arena[(prcs->pc + j + s) % MEM_SIZE] = prcs->reg[arg.int_value[0] - 1][j];
    prcs->pc = (prcs->pc + 2 + 1 + (arg.size[1] == 1 ? 1 : IND_SIZE) + (arg.size[2] == 1 ? 1 : IND_SIZE)) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s\n", i, cw->champ[i].name, op.name);
    ft_update_process(cw, prcs, op);
}

void    ft_fork(t_cw *cw, t_process *prcs, int i, t_op op)
{
    int v;
    int j;

    v = 0;
    j = -1;
    while (++j < DIR_SIZE)
        v = (256 * v + (unsigned char)cw->arena
            [(prcs->pc + 1 + j) % MEM_SIZE]) % IDX_MOD;
    if (!ft_new_prcs(&prcs,(prcs->pc + v) % MEM_SIZE))
        return ; //I Have a malloc here
    cw->nb_prcs++;
    prcs->pc = (prcs->pc + 1 + DIR_SIZE) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s\n", i, cw->champ[i].name, op.name);
    ft_update_process(cw, prcs, op);
}

void    ft_lld(t_cw *cw, t_process *prcs, int i, t_op op) // DIR | IND, REG
{
    t_arg   arg;
    int     j;

    arg.nb_args = 2;
    if (!ft_encoding_byte(cw, prcs, &arg)
        || (arg.type[0] != DIR_CODE && arg.type[0] != IND_CODE) 
        || arg.type[1] != REG_CODE)
        return ;
    j = -1;
    if (arg.type[0] == IND_CODE)
        while (++j < REG_SIZE)
            prcs->reg[arg.int_value[1] - 1][j] = cw->arena[(prcs->pc + j + arg.int_value[0]) % MEM_SIZE];
    else
        while (++j < DIR_SIZE)
             prcs->reg[arg.int_value[1] - 1][j] = arg.value[0][j];
    ft_printf("Le joueur %d(%s) a executé %s and the value in register %d is %u\n",
        i, cw->champ[i].name, op.name, arg.int_value[1], ft_str_to_int(prcs->reg[arg.int_value[1] - 1], REG_SIZE));
    prcs->pc = (prcs->pc + 2 + arg.size[0] + 1) % MEM_SIZE;
    ft_update_process(cw, prcs, op);
}

void    ft_lldi(t_cw *cw, t_process *prcs, int i, t_op op) //ARG, DIR | REG, REG
{
    t_arg           arg;
    int             j;
    unsigned int    a;
    unsigned int    b;
    unsigned int    s;

    arg.nb_args = 3;
    if (!ft_encoding_byte(cw, prcs, &arg)
        || (arg.type[1] != REG_CODE && arg.type[1] != DIR_CODE)
        || arg.type[2] != REG_CODE)
        return ;
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
    ft_printf("Le joueur %d(%s) a executé %s\n", i, cw->champ[i].name, op.name);
    ft_update_process(cw, prcs, op);
}
void    ft_lfork(t_cw *cw, t_process *prcs, int i, t_op op)
{
    int v;
    int j;

    v = 0;
    j = -1;
    while (++j < DIR_SIZE)
        v = 256 * v + (unsigned char)cw->arena[(prcs->pc + 1 + j) % MEM_SIZE];
    if (!ft_new_prcs(&prcs,(prcs->pc + v) % MEM_SIZE))
        return ; //I Have a malloc here
    cw->nb_prcs++;
    prcs->pc = (prcs->pc + 1 + DIR_SIZE) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s\n", i, cw->champ[i].name, op.name);
    ft_update_process(cw, prcs, op);
}

void    ft_aff(t_cw *cw, t_process *prcs, int i, t_op op) // REG
{
    t_arg   arg;
    //int j = -1;

    arg.nb_args = 1;
    if (!ft_encoding_byte(cw, prcs, &arg) || arg.type[0] != REG_CODE)
        return ;

    //while (++j < REG_SIZE)
      //  ft_printf("reg[%d][%d] = %u\n", arg.int_value[0] - 1, j, prcs->reg[arg.int_value[0] - 1][j]);


    ft_printf("%u\n", ft_str_to_int(prcs->reg[arg.int_value[0] - 1], REG_SIZE));
    prcs->pc = (prcs->pc + 3) % MEM_SIZE;
    ft_printf("Le joueur %d(%s) a executé %s\n", i, cw->champ[i].name, op.name);
    ft_update_process(cw, prcs, op);
}
