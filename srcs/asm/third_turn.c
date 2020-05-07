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

int		check_params_label_b(char **tmp, t_op_n n, t_asm *assm, t_op *op_tab)
{
	if ((op_tab[n.i].args[n.j] == T_DIR
				|| op_tab[n.i].args[n.j] == T_DIR + T_REG
				|| op_tab[n.i].args[n.j] == T_DIR + T_IND
				|| op_tab[n.i].args[n.j] == T_DIR + T_REG + T_IND)
			&& check_t_dir_label(tmp[n.j], assm) == 1)
	{
		if (op_tab[n.i].label == 0)
			return (n.count + 4);
		else
			return (n.count + 2);
	}
	else if ((op_tab[n.i].args[n.j] == T_IND
				|| op_tab[n.i].args[n.j] == T_IND + T_REG
				|| op_tab[n.i].args[n.j] == T_IND + T_DIR
				|| op_tab[n.i].args[n.j] == T_IND + T_DIR + T_REG)
			&& check_t_ind_label(tmp[n.j], assm) == 1)
		return (n.count + 2);
	return (return_f("FATAL ERROR - not match with the opcode\n", -1));
}

int		check_params_label(char **tmp, int i, t_asm *assm, t_op *op_tab)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (tmp[j] != NULL)
	{
		if (j + 1 > op_tab[i].nb_arg)
			return (-1);
		if ((op_tab[i].args[j] == T_REG
					|| op_tab[i].args[j] == T_REG + T_DIR
					|| op_tab[i].args[j] == T_REG + T_IND
					|| op_tab[i].args[j] == T_REG + T_IND + T_DIR)
				&& check_t_reg(tmp[j]) == 1)
			count = count + 1;
		else
			count = check_params_label_b(tmp,
					ft_init_op_n(i, j, count), assm, op_tab);
		if (count < 0)
			return (-1);
		j++;
	}
	return (count);
}

int		check_label_2(char *line, t_asm *assm, t_op *op_tab)
{
	char	**tmp;
	char	**pmt;
	int		count;
	int		i;

	count = 0;
	i = 0;
	tmp = ft_strsplit(line, ' ');
	while (op_tab[i].nb_arg != 0 && (ft_strcmp(tmp[0], op_tab[i].name) != 0))
		i++;
	if (i > 15)
		return (-1);
	pmt = ft_strsplit(tmp[1], SEPARATOR_CHAR);
	free_tab(tmp);
	if ((count = check_params_label(pmt, i, assm, op_tab)) < 0)
	{
		free_tab(pmt);
		return (-1);
	}
	free_tab(pmt);
	count++;
	if (op_tab[i].nb_arg > 1)
		count++;
	return (count);
}

int		ft_third_turn(t_asm *assm, char *str, t_op *op_tab)
{
	int	fd;
	int	r[2];

	assm->actual_bytes = 0;
	assm->line_error = 0;
	r[0] = 0;
	while (r[0] < assm->nb_label)
	{
		r[1] = 0;
		while (r[1] < assm->nb_label)
		{
			if (ft_strcmp(assm->label[r[0]].name, assm->label[r[1]].name) == 0
					&& r[0] != r[1])
				return (return_f("FATAL ERROR - same label name\n", -1));
			r[1]++;
		}
		r[0]++;
	}
	if ((fd = open(str, O_RDONLY)) < 3
			|| check_name(fd, &assm->line_error) < 0
			|| check_comment(fd, &assm->line_error) < 0
			|| ft_third_turn_b(assm, fd, op_tab) < 0)
		return (-1);
	close(fd);
	return (0);
}

int		ft_third_turn_b(t_asm *assm, int fd, t_op *op_tab)
{
	char	*line;
	char	*str_2;
	int		r;

	while (get_next_line(fd, &line) > 0)
	{
		assm->line_error = assm->line_error + 1;
		if ((str_2 = check_label(line, 0)) == NULL && f_l(&line))
			return (return_f("FATAL ERROR - problem with the label\n", -1));
		if (ft_strcmp("\0", str_2) == 0)
			;
		else
		{
			if ((r = check_label_2(str_2, assm, op_tab)) < 0
							&& f_l(&line) && f_l(&str_2))
				return (return_f("FATAL ERROR - inexistant label\n", -1));
			assm->actual_bytes = assm->actual_bytes + r;
			free(str_2);
		}
		free(line);
	}
	return (0);
}
