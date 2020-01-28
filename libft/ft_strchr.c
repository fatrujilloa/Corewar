/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:54:19 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/11 18:25:03 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t i;
	size_t len;

	i = -1;
	len = ft_strlen(s);
	while (++i < len + 1)
		if (s[i] == (char)c)
			return (((void *)&((char *)s)[i]));
	return (NULL);
}
