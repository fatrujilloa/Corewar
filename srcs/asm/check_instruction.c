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

int			check_no_space_number(char **tab, int i, int com)
{
	if (i == 0 || i == 1 || com > 0)
		return (1);
	if (tab[i][0] == 'r' || tab[i][0] == DIRECT_CHAR
			|| tab[i][0] == SEPARATOR_CHAR)
		return (1);
	if (tab[i - 1][ft_strlen(tab[i - 1]) - 1] != ',')
		return (-1);
	return (1);
}

char		*ft_return_space(char *str)
{
	str[0] = 'A';
	str[1] = '\0';
	return (str);
}

char		*ft_put_together_b(char *str, char **res)
{
	int		tab[4];

	tab[3] = 0;
	tab[0] = 0;
	tab[1] = 0;
	while (res[tab[0]])
	{
		tab[2] = 0;
		while (res[tab[0]][tab[2]])
		{
			str[tab[1]] = res[tab[0]][tab[2]];
			if (res[tab[0]][tab[2]] == COMMENT_CHAR)
				tab[3]++;
			tab[1]++;
			tab[2]++;
		}
		if (tab[0] == 0)
			str[tab[1]] = ' ';
		if (tab[0] == 0)
			tab[1]++;
		if (check_no_space_number(res, tab[0], tab[3]) < 0)
			return (ft_return_space(str));
		tab[0]++;
	}
	return (str);
}

char		*ft_put_together(char **res)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (res[i])
	{
		len = len + ft_strlen(res[i]);
		i++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (len + 2))))
		return (NULL);
	str[len + 1] = '\0';
	str = ft_put_together_b(str, res);
	return (str);
}

short		free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (1);
}
