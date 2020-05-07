/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:08:39 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 14:33:14 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_t_reg(char *str)
{
	if (*str != 'r')
		return (-1);
	str++;
	if (ft_str_isdigit(str) == 0)
		return (-1);
	if (ft_atoi(str) > 99 || ft_atoi(str) < 0)
		return (-1);
	return (1);
}

int	check_t_dir(char *str)
{
	if (*str != DIRECT_CHAR)
		return (-1);
	str++;
	if (*str == LABEL_CHAR)
	{
		str++;
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

int	check_t_ind(char *str)
{
	if (*str == LABEL_CHAR)
	{
		str++;
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
