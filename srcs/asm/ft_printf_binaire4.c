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

int				print_t_dir(char *str, t_asm *assm, int j, t_op *op_tab)
{
	int i;

	i = 0;
	if (*str != DIRECT_CHAR)
		return (-1);
	str++;
	assm->quote = j;
	if (*str == LABEL_CHAR)
		return (print_t_dir_b(str, i, assm, op_tab));
	if (*str == '-')
	{
		str++;
		if (op_tab[j].label == 0)
			print_nb_bytes(4, assm, puissance(16, 8) - ft_atoi(str));
		else
			print_nb_bytes(2, assm, 65536 - ft_atoi(str));
	}
	else
	{
		if (op_tab[j].label == 0)
			print_nb_bytes(4, assm, ft_atoi(str));
		else
			print_nb_bytes(2, assm, ft_atoi(str));
	}
	return (1);
}

int				print_t_ind(char *str, t_asm *assm)
{
	int	i;

	i = 0;
	if (*str == LABEL_CHAR)
	{
		str++;
		while (ft_strcmp(str, assm->label[i].name) != 0)
			i++;
		if (assm->label[i].place + PROG_NAME_LENGTH + COMMENT_LENGTH + 16
				- assm->actual_bytes_l >= 0)
			print_nb_bytes(2, assm, assm->label[i].place + PROG_NAME_LENGTH
					+ COMMENT_LENGTH + 16 - assm->actual_bytes_l);
		else
			print_nb_bytes(2, assm, 65536 + (assm->label[i].place +
				PROG_NAME_LENGTH + COMMENT_LENGTH + 16 - assm->actual_bytes_l));
		return (1);
	}
	if (*str == '-')
	{
		str++;
		print_nb_bytes(2, assm, 65536 - ft_atoi(str));
	}
	else
		print_nb_bytes(2, assm, ft_atoi(str));
	return (1);
}

void			print_nb_bytes(int bytes, t_asm *assm, unsigned int nb)
{
	int	i;
	int	c1;
	int	c10;

	i = 1;
	while (nb > 0 && bytes * 2 - i > 0)
	{
		c10 = nb / (puissance(16, bytes * 2 - i));
		nb = nb - c10 * (puissance(16, bytes * 2 - i));
		c1 = nb / (puissance(16, bytes * 2 - i - 1));
		nb = nb - c1 * (puissance(16, bytes * 2 - i - 1));
		assm->tab[assm->actual_bytes + (i - 1) / 2] = 16 * c10 + c1;
		i = i + 2;
	}
	assm->actual_bytes = assm->actual_bytes + bytes;
}

void			ft_print_params(char **tmp, int i, t_asm *assm, t_op *op_tab)
{
	int	j;
	int	u;

	u = 3;
	j = 0;
	while (j < op_tab[i].nb_arg && u > 0)
	{
		if (print_t_reg(tmp[j], assm) == 1)
			;
		else if (print_t_dir(tmp[j], assm, i, op_tab) == 1)
			;
		else if (print_t_ind(tmp[j], assm) == 1)
			u = 2;
		j++;
	}
}

int				print_line_instruc(char *line, t_asm *assm, t_op *op_tab)
{
	char	**tmp;
	char	**pmt;
	int		i;

	i = 0;
	tmp = ft_strsplit(line, ' ');
	while (op_tab[i].nb_arg != 0 && (ft_strcmp(tmp[0], op_tab[i].name) != 0))
		i++;
	if (i > 15)
		return (-1);
	assm->tab[assm->actual_bytes] = op_tab[i].opcode;
	assm->actual_bytes++;
	pmt = ft_strsplit(tmp[1], SEPARATOR_CHAR);
	free_tab(tmp);
	if (op_tab[i].nb_arg > 1)
		ft_char_argu(pmt, i, assm, op_tab);
	ft_print_params(pmt, i, assm, op_tab);
	free_tab(pmt);
	return (0);
}
