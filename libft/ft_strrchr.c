/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:13:46 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/06 00:38:22 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int res;

	i = 0;
	res = -1;
	if (c == '\0')
	{
		while (s[i])
			i++;
		return ((char *)(&(s[i])));
	}
	while (s[i])
	{
		if (s[i] == (char)c)
			res = i;
		i++;
	}
	if (res == -1)
		return (NULL);
	return ((char *)(&(s[res])));
}
