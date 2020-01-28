/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:36:03 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/10 15:10:22 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*ssrc;
	unsigned char	*sdst;
	unsigned int	i;

	i = 0;
	ssrc = (unsigned char *)src;
	sdst = (unsigned char *)dst;
	while (i < n)
	{
		sdst[i] = ssrc[i];
		if (ssrc[i] == (unsigned char)c)
			return ((void *)&(sdst[i + 1]));
		i++;
	}
	return (NULL);
}
