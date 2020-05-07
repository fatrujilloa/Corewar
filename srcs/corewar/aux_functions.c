/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:26:47 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/06 16:27:20 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

unsigned int	ft_max(unsigned int a, unsigned int b)
{
	return (a > b ? a : b);
}

void			ft_strnrev(unsigned char *str, unsigned int size)
{
	unsigned int	i;
	char			tmp;

	i = 0;
	while (i < size / 2)
	{
		tmp = str[i];
		str[i] = str[size - 1 - i];
		str[size - 1 - i] = tmp;
		i++;
	}
}

int				ft_isstrnum(char *str)
{
	int i;

	if (!str || !*str)
		return (0);
	if (*str == '+')
		str++;
	if (!*str)
		return (0);
	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

long long int	ft_mod_atoi(const char *str)
{
	size_t				i;
	long long int		number;

	i = 0;
	number = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = 10 * number + str[i++] - 48;
		if (number > 4294967295)
			return (-1);
	}
	return (number);
}

void			ft_lstdelnext(t_process **lst, t_process **prev)
{
	t_process	*tmp;

	if (!lst || !(*lst))
		return ;
	if (!prev)
	{
		tmp = *lst;
		*lst = tmp->next ? tmp->next : NULL;
		free(tmp);
		return ;
	}
	if ((tmp = (*prev)->next) == NULL)
		return ;
	(*prev)->next = tmp->next;
	free(tmp);
}
