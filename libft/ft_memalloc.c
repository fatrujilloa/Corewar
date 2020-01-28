/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:57:26 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/06 00:13:49 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*memzone;

	memzone = malloc(size);
	if (!memzone)
		return (NULL);
	ft_bzero(memzone, size);
	return (memzone);
}
