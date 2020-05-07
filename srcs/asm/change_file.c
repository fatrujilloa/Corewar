/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:46:29 by gmoindro          #+#    #+#             */
/*   Updated: 2020/01/17 16:47:22 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static char	*ft_strcat_2(char *s1, const char *s2)
{
	int		len;
	int		i;
	int		len_2;
	char	*s;

	len = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	if (!(s = (char *)malloc(sizeof(char) * (len + len_2 + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		s[len] = ((char *)s2)[i];
		len++;
		i++;
	}
	s[len] = '\0';
	return (s);
}

static int	ft_strrchr_nbr(const char *s, int c)
{
	int		i;
	int		res;

	i = 0;
	res = -1;
	if (c == '\0')
	{
		while (s[i])
			i++;
		return (i);
	}
	while (s[i])
	{
		if (s[i] == (char)c)
			res = i;
		i++;
	}
	if (res == -1)
		return (-1);
	return (res);
}

char		*change_s_cor(char *str)
{
	char	*s;
	char	*s_2;

	if (ft_strchr(str, '.') == NULL)
	{
		return_f("FATAL ERROR - your file needs a .s extension\n", 0);
		return (NULL);
	}
	if (ft_strcmp(ft_strrchr(str, '.'), ".s"))
	{
		return_f("FATAL ERROR - your file needs a .s extension\n", 0);
		return (NULL);
	}
	s = ft_strsub(str, 0, ft_strrchr_nbr(str, '.'));
	s_2 = ft_strcat_2(s, ".cor\0");
	free(s);
	return (s_2);
}
