/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_turn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:05:15 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 16:55:16 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

char	*check_label(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			;
		else if (line[i] == COMMENT_CHAR)
			return ("\0");
		else if (ft_strchr(LABEL_CHARS, line[i]) != NULL)
		{
			while (line[i] && ft_strchr(LABEL_CHARS, line[i]) != NULL)
				i++;
			if (line[i] && line[i] == LABEL_CHAR)
			{
				line = line + i + 1;
				i = -1;
			}
			else
				return (suppr_space_label_b(line, i));
		}
		else
			return (NULL);
		i++;
	}
	return ("\0");
}
