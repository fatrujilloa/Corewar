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

int				write_comment_c(char *line, int *len_comment, t_asm *assm)
{
	int		r;

	if ((r = ft_write_next(line, &(assm->quote), assm)) < 0)
		return (-1);
	*len_comment = *len_comment + r;
	if (assm->quote == 1)
	{
		assm->tab[assm->actual_bytes] = '\n';
		assm->actual_bytes++;
		*len_comment = *len_comment + 1;
	}
	if (assm->quote == 2)
		return (*len_comment);
	return (1);
}

void			change_assm_l(t_asm *assm, int *len_comment)
{
	assm->tab[assm->actual_bytes] = '\n';
	assm->actual_bytes++;
	*len_comment = *len_comment + 1;
}

int				write_comment_b(char *line, int *comment,
					int *len_comment, t_asm *assm)
{
	char	*str;

	if (*comment == 0 && (str = ft_strstr(line, COMMENT_CMD_STRING)))
	{
		*comment = *comment + 1;
		if (check_nothing_before(line, COMMENT_CMD_STRING, 0) == 0)
			return (-1);
		if ((*len_comment = ft_write_begin(str, COMMENT_CMD_STRING,
					&(assm->quote), assm)) < 0)
			return (-1);
		if (assm->quote == 1)
			change_assm_l(assm, len_comment);
		if (assm->quote == 2)
			return (*len_comment);
	}
	else if (*comment == 0 && ft_strstr(line, COMMENT_CMD_STRING) == NULL)
	{
		if (check_nothing(line) == 0)
			return (-1);
	}
	else
		return (write_comment_c(line, len_comment, assm));
	return (1);
}

int				write_comment(int fd, t_asm *assm)
{
	char	*line;
	char	*str_2;
	int		comment;
	int		len_comment;

	comment = 0;
	assm->quote = 0;
	ft_print_in_actual("0\0", assm, 4);
	str_2 = ft_itoa_base(assm->len_bytes, 16);
	ft_print_in_actual(str_2, assm, 4);
	free(str_2);
	while (get_next_line(fd, &line) > 0)
	{
		if (write_comment_b(line, &comment, &len_comment, assm) < 0
						&& f_l(&line))
			return (-1);
		free(line);
		if (assm->quote == 2)
			return (len_comment);
	}
	return (-1);
}

int				ft_write_next(char *line, int *quote, t_asm *assm)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
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
