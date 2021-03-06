/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 09:04:34 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/04 13:55:11 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		len;

	len = ft_strlen(s1);
	i = 0;
	while (s2[i] && i < n)
	{
		s1[len] = (((char *)s2)[i]);
		len++;
		i++;
	}
	s1[len] = '\0';
	return (s1);
}
