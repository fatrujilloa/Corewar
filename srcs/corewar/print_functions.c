/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:35:03 by rbeaufre          #+#    #+#             */
/*   Updated: 2020/02/02 19:06:42 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"


void    ft_print_op(t_process *prcs, t_arg arg, t_op op)
{
    int i;
    int aux;
    
    ft_printf("P   %u | %s ", prcs->nb + 1, op.name);
    aux = (op.opcode == 11) ? arg.nb_args - 2 : arg.nb_args;
    i = -1;
    while (++i < aux)
    {
		ft_printf("%s%d", arg.size[i] == 1 ? "r" : "", arg.size[i] == 1 ? (int)arg.int_value[i] : (int)arg.real_value[i]);
        //ft_printf("%s%u", arg.size[i] == 1 ? "r" : "", arg.int_value[i]);
        if (i < arg.nb_args - 1)
            ft_printf(" ");
        else
            ft_printf("\n");
    }
    if (op.opcode == 11)
    {
        ft_printf("%d ", (int)prcs->arg.real_value[1]);
        ft_printf("%d\n", (int)ft_str_to_int(prcs->reg[prcs->arg.int_value[2] - 1], REG_SIZE));
       // ft_printf("prcs->arg.int_value[2] - 1 = %u, prcs->arg.type[2] = %d, prcs->arg.real_value[2] = %d\n", prcs->arg.int_value[2] - 1, prcs->arg.int_value[2] - 1, prcs->arg.real_value[2]);
        ft_printf("      | -> store to %d + %d = %d (with pc and mod %u)\n",
            (int)prcs->arg.real_value[1], (int)ft_str_to_int(prcs->reg[prcs->arg.int_value[2] - 1], REG_SIZE),
            (int)prcs->arg.real_value[1] + (int)ft_str_to_int(prcs->reg[prcs->arg.int_value[2] - 1], REG_SIZE),
            (int)((prcs->pc + (prcs->arg.real_value[1] + ft_str_to_int(prcs->reg[prcs->arg.int_value[2] - 1], REG_SIZE) % IDX_MOD)) % MEM_SIZE));
    }
}

void	ft_print_prcs(t_process *prcs)
{
	ft_printf("Printing process:\n");
	ft_printf("Carry = %d, PC = %d, Wait_until = %d, alive = %d\n", prcs->carry, prcs->pc, prcs->wait_until, prcs->alive);
	if (!prcs->next)
		{
			ft_printf("prcs->next = NULL\n");
			//free(prcs);
			//ft_printf("We freed prcs\n");
		}
}

void		ft_print_arena(t_cw *cw)
{
	int s;
	int i;

	s = 0;
	while (s * s < MEM_SIZE)
		s++;
	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%02x ", (unsigned char)cw->arena[i]);
		i++;
		if (i % s == 0)
			ft_putchar('\n');
	}
}

int	ft_print_error(char *str)
{
	char c;

	c = '\n';
	write(2, "Error output: ", 14);
	write(2, str, ft_strlen(str));
	write(2, &c, 1);
	return (1);
}
