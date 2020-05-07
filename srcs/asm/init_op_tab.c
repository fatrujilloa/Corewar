/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_op_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:26:24 by gmoindro          #+#    #+#             */
/*   Updated: 2020/01/16 17:50:52 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

char	*name_op_tab(char *str)
{
	char	*s;
	int		i;
	int		len;

	len = ft_strlen(str);
	i = 0;
	if (!(s = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void	init_op_tab_1(t_op *op_tab)
{
	op_tab->name = name_op_tab("live");
	op_tab->nb_arg = 1;
	op_tab->args[0] = 2;
	op_tab->args[1] = 0;
	op_tab->args[2] = 0;
	op_tab->opcode = 1;
	op_tab->cycle = 10;
	op_tab->description = NULL;
	op_tab->octal = 0;
	op_tab->label = 0;
}

void	init_op_tab_2(t_op *op_tab)
{
	op_tab->name = name_op_tab("ld");
	op_tab->nb_arg = 2;
	op_tab->args[0] = 6;
	op_tab->args[1] = 1;
	op_tab->args[2] = 0;
	op_tab->opcode = 2;
	op_tab->cycle = 5;
	op_tab->description = NULL;
	op_tab->octal = 1;
	op_tab->label = 0;
}

void	init_op_tab_3(t_op *op_tab)
{
	op_tab->name = name_op_tab("st");
	op_tab->nb_arg = 2;
	op_tab->args[0] = 1;
	op_tab->args[1] = 5;
	op_tab->args[2] = 0;
	op_tab->opcode = 3;
	op_tab->cycle = 5;
	op_tab->description = NULL;
	op_tab->octal = 1;
	op_tab->label = 0;
}

void	init_op_tab_4(t_op *op_tab)
{
	op_tab->name = name_op_tab("add");
	op_tab->nb_arg = 3;
	op_tab->args[0] = 1;
	op_tab->args[1] = 1;
	op_tab->args[2] = 1;
	op_tab->opcode = 4;
	op_tab->cycle = 10;
	op_tab->description = NULL;
	op_tab->octal = 1;
	op_tab->label = 0;
}
