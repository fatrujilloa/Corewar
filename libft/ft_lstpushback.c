/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 11:03:38 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/11 11:14:19 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list **alst, t_list *new)
{
	t_list *tmp;

	if (!new || !alst)
		return ;
	if (!(*alst))
		*alst = new;
	else
	{
		tmp = *alst;
		while (tmp)
			tmp = tmp->next;
		tmp->next = new;
	}
}
