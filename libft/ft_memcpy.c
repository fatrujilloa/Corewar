/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:55:19 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/10 14:43:25 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*tmp1;
	char		*tmp2;

	if (dst == NULL && src == NULL)
		return (NULL);
	tmp1 = (const char *)src;
	tmp2 = (char *)dst;
	while (n--)
		*tmp2++ = *tmp1++;
	return (dst);
}
