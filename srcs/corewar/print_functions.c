/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:35:03 by rbeaufre          #+#    #+#             */
/*   Updated: 2020/02/03 23:20:41 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

char    *ft_spaces(unsigned int n)
{
    if (n < 10)
        return ("    ");
    if (n < 100)
        return ("   ");
    if (n < 1000)
        return ("  ");
    else
        return (" ");
}

void    ft_print_op(t_process *prcs, t_arg arg, t_op op)
{
    int i;
    
    ft_printf("P%s%u | %s ", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name);
    i = -1;
    while (++i < arg.nb_args)
    {
		ft_printf("%s%d", arg.size[i] == 1 ? "r" : "", arg.size[i] == 1 ? (int)arg.int_value[i] : (int)arg.real_value[i]);
        //ft_printf("%s%u", arg.size[i] == 1 ? "r" : "", arg.int_value[i]);
        if (i < arg.nb_args - 1)
            ft_printf(" ");
        else
            ft_printf("\n");
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
