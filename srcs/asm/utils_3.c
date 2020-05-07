/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:08:54 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 14:33:27 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int	check_label_dir(char *str, t_asm *assm)
{
	int	i;

	i = 0;
	while (i < assm->nb_label)
	{
		if (ft_strcmp(str, assm->label[i].name) == 0)
			return (1);
		i++;
	}
	return (-1);
}

int	check_t_dir_label_b(char c, char *str)
{
	if (c == '-')
	{
		if (ft_str_isdigit(str + 1) == 0)
			return (-1);
	}
	else
	{
		if (ft_str_isdigit(str) == 0)
			return (-1);
	}
	return (1);
}

int	check_t_dir_label(char *str, t_asm *assm)
{
	if (*str != DIRECT_CHAR)
		return (-1);
	str++;
	if (*str == LABEL_CHAR)
	{
		str++;
		if (check_label_dir(str, assm) < 0)
			return (-1);
		while (*str)
		{
			if (ft_strchr(LABEL_CHARS, *str) == NULL)
				return (-1);
			str++;
		}
		return (1);
	}
	return (check_t_dir_label_b(*str, str));
}

int	check_t_ind_label(char *str, t_asm *assm)
{
	if (*str == LABEL_CHAR)
	{
		str++;
		if (check_label_dir(str, assm) < 0)
			return (-1);
		while (*str)
		{
			if (ft_strchr(LABEL_CHARS, *str) == NULL)
				return (-1);
			str++;
		}
		return (1);
	}
	if (*str == '-')
	{
		if (ft_str_isdigit(str + 1) == 0)
			return (-1);
	}
	else
	{
		if (ft_str_isdigit(str) == 0)
			return (-1);
	}
	return (1);
}
