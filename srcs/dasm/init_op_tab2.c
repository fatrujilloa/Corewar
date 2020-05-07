/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_op_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:56:31 by gmoindro          #+#    #+#             */
/*   Updated: 2020/01/18 18:57:52 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

void	init_op_tab_5(t_op *op_tab)
{
	op_tab->name = name_op_tab("sub");
	op_tab->nb_arg = 3;
	op_tab->args[0] = 1;
	op_tab->args[1] = 1;
	op_tab->args[2] = 1;
	op_tab->opcode = 5;
	op_tab->cycle = 10;
	op_tab->description = NULL;
	op_tab->octal = 1;
	op_tab->label = 0;
}

void	init_op_tab_6(t_op *op_tab)
{
	op_tab->name = name_op_tab("and");
	op_tab->nb_arg = 3;
	op_tab->args[0] = 7;
	op_tab->args[1] = 7;
	op_tab->args[2] = 1;
	op_tab->opcode = 6;
	op_tab->cycle = 6;
	op_tab->description = NULL;
	op_tab->octal = 1;
	op_tab->label = 0;
}

void	init_op_tab_7(t_op *op_tab)
{
	op_tab->name = name_op_tab("or");
	op_tab->nb_arg = 3;
	op_tab->args[0] = 7;
	op_tab->args[1] = 7;
	op_tab->args[2] = 1;
	op_tab->opcode = 7;
	op_tab->cycle = 6;
	op_tab->description = NULL;
	op_tab->octal = 1;
	op_tab->label = 0;
}

void	init_op_tab_8(t_op *op_tab)
{
	op_tab->name = name_op_tab("xor");
	op_tab->nb_arg = 3;
	op_tab->args[0] = 7;
	op_tab->args[1] = 7;
	op_tab->args[2] = 1;
	op_tab->opcode = 8;
	op_tab->cycle = 6;
	op_tab->description = NULL;
	op_tab->octal = 1;
	op_tab->label = 0;
}

void	init_op_tab_9(t_op *op_tab)
{
	op_tab->name = name_op_tab("zjmp");
	op_tab->nb_arg = 1;
	op_tab->args[0] = 2;
	op_tab->args[1] = 0;
	op_tab->args[2] = 0;
	op_tab->opcode = 9;
	op_tab->cycle = 20;
	op_tab->description = NULL;
	op_tab->octal = 0;
	op_tab->label = 1;
}
