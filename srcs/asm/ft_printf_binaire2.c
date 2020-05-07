/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_binaire.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:44:38 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 15:45:29 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int				ft_write_begin(char *line, char *str, int *quote, t_asm *assm)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (str[i] && line[i] == str[i])
		i++;
	while (line[i])
	{
		if (line[i] == '"' && *quote < 2)
			*quote = *quote + 1;
		else if (*quote == 1)
		{
			assm->tab[assm->actual_bytes] = line[i];
			assm->actual_bytes++;
			len++;
		}
		else if (line[i] == COMMENT_CHAR)
			break ;
		else if (*quote != 1 && line[i] != ' '
				&& line[i] != '\t' && line[i] != '\n')
			return (-1);
		i++;
	}
	return (len);
}

unsigned char	ft_deci(char c10, char c1)
{
	if (c10 == 'A' || c10 == 'B' || c10 == 'C'
			|| c10 == 'D' || c10 == 'E' || c10 == 'F')
		c10 = c10 - 55;
	else
		c10 = c10 - 48;
	if (c1 == 'A' || c1 == 'B' || c1 == 'C'
			|| c1 == 'D' || c1 == 'E' || c1 == 'F')
		c1 = c1 - 55;
	else
		c1 = c1 - 48;
	return (c10 * 16 + c1);
}

void			ft_print_in_actual(char *str, t_asm *assm, int size)
{
	int	len;
	int	i;

	i = 1;
	len = ft_strlen(str) - 1;
	while (len >= 0)
	{
		if (len - 1 >= 0)
		{
			assm->tab[assm->actual_bytes + size - i] = ft_deci(str[len - 1],
					str[len]);
			len = len - 2;
		}
		else
		{
			assm->tab[assm->actual_bytes + size - i] = ft_deci('0', str[len]);
			len--;
		}
		i++;
	}
	assm->actual_bytes = assm->actual_bytes + size;
}

int				write_name_c(char *line, int *len_name, t_asm *assm)
{
	int		r;

	if ((r = ft_write_next(line, &(assm->quote), assm)) < 0)
		return (-1);
	*len_name = *len_name + r;
	if (assm->quote == 1)
	{
		assm->tab[assm->actual_bytes] = '\n';
		assm->actual_bytes++;
		*len_name = *len_name + 1;
	}
	if (assm->quote == 2)
		return (*len_name);
	return (1);
}

int				write_name_b(char *line, int *name, int *len_name, t_asm *assm)
{
	char	*str;

	if (*name == 0 && (str = ft_strstr(line, NAME_CMD_STRING)))
	{
		*name = *name + 1;
		if (check_nothing_before(line, NAME_CMD_STRING, 0) == 0)
			return (-1);
		if ((*len_name = ft_write_begin(str, NAME_CMD_STRING,
				&(assm->quote), assm)) < 0)
			return (-1);
		if (assm->quote == 1)
			change_assm_l(assm, len_name);
		if (assm->quote == 2)
			return (*len_name);
	}
	else if (*name == 0 && ft_strstr(line, NAME_CMD_STRING) == NULL)
	{
		if (check_nothing(line) == 0)
			return (-1);
	}
	else
		return (write_name_c(line, len_name, assm));
	return (1);
}
