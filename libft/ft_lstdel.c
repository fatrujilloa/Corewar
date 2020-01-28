/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 13:58:03 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/07 14:16:08 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *nxt;

	if (!alst)
		return ;
	tmp = *alst;
	while (tmp)
	{
		nxt = tmp->next;
		ft_lstdelone(&tmp, del);
		tmp = nxt;
	}
	(*alst) = NULL;
}
