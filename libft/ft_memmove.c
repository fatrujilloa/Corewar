/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 11:02:02 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/10 14:43:07 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*t_dst;
	const unsigned char		*t_src;
	size_t					i;

	t_dst = (unsigned char *)dst;
	t_src = (const unsigned char *)src;
	if ((!dst && !src))
		return (NULL);
	if (t_src < t_dst)
	{
		while (len-- > 0)
			t_dst[len] = t_src[len];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			t_dst[i] = t_src[i];
			i++;
		}
	}
	return (dst);
}
