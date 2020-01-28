/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 14:14:35 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/06/10 13:21:54 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*res;
	size_t	i;

	if (!(res = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	i = 0;
	while (i < size)
		res[i++] = '\0';
	res[i] = '\0';
	return (res);
}
