/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:35:44 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 17:52:03 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

char	**init_tab(void)
{
	char	**tab;
	int		nb;
	int		i[2];

	nb = PROG_NAME_LENGTH + COMMENT_LENGTH + (CHAMP_MAX_SIZE / 2);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb + 1))))
		return (NULL);
	tab[nb] = NULL;
	if (!(tab[0] = (char *)malloc(sizeof(char) * (PROG_NAME_LENGTH + 1))))
		return (NULL);
	tab[0][PROG_NAME_LENGTH] = '\0';
	if (!(tab[1] = (char *)malloc(sizeof(char) * (COMMENT_LENGTH + 1))))
		return (NULL);
	tab[1][COMMENT_LENGTH] = '\0';
	i[0] = 2;
	while (i[0] < nb)
	{
		i[1] = -1;
		if (!(tab[i[0]] = (char *)malloc(sizeof(char) * (41))))
			return (NULL);
		while (++i[1] < 41)
			tab[i[0]][i[1]] = 0;
		i[0]++;
	}
	return (tab);
}

void	init_buffer(t_dasm *dasm)
{
	int	r;

	r = dasm->ret;
	while (r < COMMENT_LENGTH + PROG_NAME_LENGTH + CHAMP_MAX_SIZE + 17)
	{
		dasm->buf[r] = 0;
		r++;
	}
}
