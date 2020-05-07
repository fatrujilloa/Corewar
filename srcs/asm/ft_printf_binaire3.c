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

int				write_name(int fd, t_asm *assm)
{
	char	*line;
	char	*str_2;
	int		name;
	int		len_name;

	name = 0;
	assm->quote = 0;
	str_2 = ft_itoa_base(COREWAR_EXEC_MAGIC, 16);
	ft_print_in_actual(str_2, assm, 4);
	free(str_2);
	while (get_next_line(fd, &line) > 0)
	{
		if (write_name_b(line, &name, &len_name, assm) < 0
				&& f_l(&line))
			return (-1);
		free(line);
		if (assm->quote == 2)
			return (len_name);
	}
	return (-1);
}

unsigned long	puissance(unsigned long nb, int p)
{
	unsigned long	nb_f;

	nb_f = nb;
	if (p == 0)
		return (1);
	while (p > 1)
	{
		nb_f = nb_f * nb;
		p--;
	}
	return (nb_f);
}

void			ft_char_argu(char **tmp, int i, t_asm *assm, t_op *op_tab)
{
	int	j;
	int	count;

	count = 0;
	j = 0;
	while (j < op_tab[i].nb_arg)
	{
		if (check_t_reg(tmp[j]) == 1)
			count = count + puissance(2, (6 - 2 * j));
		else if (check_t_dir(tmp[j]) == 1)
			count = count + puissance(2, (7 - 2 * j));
		else
		{
			count = count + puissance(2, (6 - 2 * j));
			count = count + puissance(2, (7 - 2 * j));
		}
		j++;
	}
	assm->tab[assm->actual_bytes] = count;
	assm->actual_bytes++;
}

int				print_t_reg(char *str, t_asm *assm)
{
	if (*str != 'r')
		return (-1);
	str++;
	if (ft_str_isdigit(str) == 0)
		return (-1);
	assm->tab[assm->actual_bytes] = ft_atoi(str);
	assm->actual_bytes++;
	return (1);
}

int				print_t_dir_b(char *str, int i, t_asm *assm, t_op *op_tab)
{
	str++;
	while (ft_strcmp(str, assm->label[i].name) != 0)
		i++;
	if (op_tab[assm->quote].label == 0)
	{
		if (assm->label[i].place + PROG_NAME_LENGTH
				+ COMMENT_LENGTH + 16 - assm->actual_bytes_l >= 0)
			print_nb_bytes(4, assm, assm->label[i].place
					+ PROG_NAME_LENGTH + COMMENT_LENGTH + 16
					- assm->actual_bytes_l);
		else
			print_nb_bytes(4, assm, puissance(16, 8)
					+ (assm->label[i].place + PROG_NAME_LENGTH
						+ COMMENT_LENGTH + 16 - assm->actual_bytes_l));
		return (1);
	}
	if (assm->label[i].place + PROG_NAME_LENGTH
			+ COMMENT_LENGTH + 16 - assm->actual_bytes_l >= 0)
		print_nb_bytes(2, assm, assm->label[i].place + PROG_NAME_LENGTH
				+ COMMENT_LENGTH + 16 - assm->actual_bytes_l);
	else
		print_nb_bytes(2, assm, 65536
				+ (assm->label[i].place + PROG_NAME_LENGTH
					+ COMMENT_LENGTH + 16 - assm->actual_bytes_l));
	return (1);
}
