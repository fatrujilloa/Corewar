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

void	init_op_tab_15(t_op *op_tab)
{
	op_tab->name = name_op_tab("lfork");
	op_tab->nb_arg = 1;
	op_tab->args[0] = 2;
	op_tab->args[1] = 0;
	op_tab->args[2] = 0;
	op_tab->opcode = 15;
	op_tab->cycle = 1000;
	op_tab->description = NULL;
	op_tab->octal = 0;
	op_tab->label = 1;
}

void	init_op_tab_16(t_op *op_tab)
{
	op_tab->name = name_op_tab("aff");
	op_tab->nb_arg = 1;
	op_tab->args[0] = 1;
	op_tab->args[1] = 0;
	op_tab->args[2] = 0;
	op_tab->opcode = 16;
	op_tab->cycle = 2;
	op_tab->description = NULL;
	op_tab->octal = 1;
	op_tab->label = 0;
}

void	init_op_tab_17(t_op *op_tab)
{
	op_tab->name = NULL;
	op_tab->nb_arg = 0;
	op_tab->args[0] = 0;
	op_tab->args[1] = 0;
	op_tab->args[2] = 0;
	op_tab->opcode = 0;
	op_tab->cycle = 0;
	op_tab->description = NULL;
	op_tab->octal = 0;
	op_tab->label = 0;
}

t_op	*init_op_tab(void)
{
	t_op	*op_tab;

	if (!(op_tab = (t_op *)malloc(sizeof(t_op) * 17)))
		return (NULL);
	init_op_tab_1(&(op_tab[0]));
	init_op_tab_2(&(op_tab[1]));
	init_op_tab_3(&(op_tab[2]));
	init_op_tab_4(&(op_tab[3]));
	init_op_tab_5(&(op_tab[4]));
	init_op_tab_6(&(op_tab[5]));
	init_op_tab_7(&(op_tab[6]));
	init_op_tab_8(&(op_tab[7]));
	init_op_tab_9(&(op_tab[8]));
	init_op_tab_10(&(op_tab[9]));
	init_op_tab_11(&(op_tab[10]));
	init_op_tab_12(&(op_tab[11]));
	init_op_tab_13(&(op_tab[12]));
	init_op_tab_14(&(op_tab[13]));
	init_op_tab_15(&(op_tab[14]));
	init_op_tab_16(&(op_tab[15]));
	init_op_tab_17(&(op_tab[16]));
	return (op_tab);
}
