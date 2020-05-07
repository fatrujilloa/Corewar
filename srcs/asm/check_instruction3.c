/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:47:26 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 16:47:42 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

char		*ft_strcat_mal(char *s1, const char *s2)
{
	int		len;
	int		i;
	char	*str;

	if (!(str = (char *)malloc(sizeof(char)
				* (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (i < len && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] && i < (int)ft_strlen(s2))
	{
		str[len + i] = ((char *)s2)[i];
		i++;
	}
	str[len + i] = '\0';
	return (str);
}

char		*suppr_space_b(char *line, int j)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(line) + 2))))
		return (NULL);
	while (i < j)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = ' ';
	i++;
	while (line[i - 1])
	{
		str[i] = line[i - 1];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char		*suppr_space(char *line, int j)
{
	char	**res;
	char	**res_2;
	char	*str[3];

	if (line[j] == '-' || line[j] == DIRECT_CHAR)
	{
		if (!(str[1] = suppr_space_b(line, j)))
			return (NULL);
	}
	else
		str[1] = ft_strcat_mal("\0", line);
	res = ft_split_whitespaces(str[1]);
	free(str[1]);
	str[0] = ft_put_together(res);
	free_tab(res);
	res_2 = ft_strsplit(str[0], '#');
	free(str[0]);
	str[2] = ft_strcat_mal("\0", res_2[0]);
	free_tab(res_2);
	return (str[2]);
}

char		*suppr_space_label_b(char *line, int i)
{
	if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
			|| line[i] == '-' || line[i] == DIRECT_CHAR)
		return (suppr_space(line, i));
	return (NULL);
}
