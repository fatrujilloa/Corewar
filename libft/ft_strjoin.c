/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:53:54 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/10 17:36:30 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	size = 0;
	if (s1)
		size += ft_strlen(s1);
	if (s2)
		size += ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	if (s1 && s2)
	{
		ft_strcat(ft_strcpy(res, s1), s2);
		return (res);
	}
	else if (s1 != NULL && s2 == NULL)
		return (ft_strcpy(res, s1));
	else if (s1 == NULL && s2 != NULL)
		return (ft_strcpy(res, s2));
	else
		return (NULL);
}
