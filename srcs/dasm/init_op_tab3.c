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

void	init_op_tab_10(t_op *op_tab)
{
	op_tab->name = name_op_tab("ldi");
	op_tab->nb_arg = 3;
	op_tab->args[0] = 7;
	op_tab->args[1] = 3;
	op_tab->args[2] = 1;
	op_tab->opcode = 10;
	op_tab->cycle = 25;
	op_tab->description = NULL;
	op_tab->octal = 1;
	op_tab->label = 1;
}

void	init_op_tab_11(t_op *op_tab)
{
	op_tab->name = name_op_tab("sti");
	op_tab->nb_arg = 3;
	op_tab->args[0] = 1;
	op_tab->args[1] = 7;
	op_tab->args[2] = 3;
	op_tab->opcode = 11;
	op_tab->cycle = 25;
	op_tab->description = NULL;
	op_tab->octal = 1;
	op_tab->label = 1;
}

void	init_op_tab_12(t_op *op_tab)
{
	op_tab->name = name_op_tab("fork");
	op_tab->nb_arg = 1;
	op_tab->args[0] = 2;
	op_tab->args[1] = 0;
	op_tab->args[2] = 0;
	op_tab->opcode = 12;
	op_tab->cycle = 800;
	op_tab->description = NULL;
	op_tab->octal = 0;
	op_tab->label = 1;
}

void	init_op_tab_13(t_op *op_tab)
{
	op_tab->name = name_op_tab("lld");
	op_tab->nb_arg = 2;
	op_tab->args[0] = 6;
	op_tab->args[1] = 1;
	op_tab->args[2] = 0;
	op_tab->opcode = 13;
	op_tab->cycle = 10;
	op_tab->description = NULL;
	op_tab->octal = 1;
	op_tab->label = 0;
}

void	init_op_tab_14(t_op *op_tab)
{
	op_tab->name = name_op_tab("lldi");
	op_tab->nb_arg = 3;
	op_tab->args[0] = 7;
	op_tab->args[1] = 3;
	op_tab->args[2] = 1;
	op_tab->opcode = 14;
	op_tab->cycle = 50;
	op_tab->description = NULL;
	op_tab->octal = 1;
	op_tab->label = 1;
}
