/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:24:25 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/10 12:02:39 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;

	if (!(res = (t_list *)malloc(sizeof(t_list))))
		return (0);
	res = f(lst);
	if (lst->next)
	{
		res->next = ft_lstmap(lst->next, f);
		if (res->next == NULL)
		{
			free(res);
			return (NULL);
		}
	}
	else
		res->next = NULL;
	return (res);
}
