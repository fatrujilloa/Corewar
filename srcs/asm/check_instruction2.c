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

char		*suppr_space_label(char *line, t_asm *assm, int i)
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
				assm->nb_label++;
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

int			check_params_b(char **tmp, t_op_n n, t_op *op_tab)
{
	if ((op_tab[n.i].args[n.j] == T_DIR
		|| op_tab[n.i].args[n.j] == T_DIR + T_REG
		|| op_tab[n.i].args[n.j] == T_DIR + T_IND
		|| op_tab[n.i].args[n.j] == T_DIR + T_REG + T_IND)
			&& check_t_dir(tmp[n.j]) == 1)
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
			&& check_t_ind(tmp[n.j]) == 1)
		return (n.count + 2);
	return (return_f("FATAL ERROR - not match with the opcode\n", -1));
}

int			check_params(char **tmp, int i, t_op *op_tab)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (tmp[j] != NULL)
	{
		if (j + 1 > op_tab[i].nb_arg)
			return (return_f("FATAL ERROR - too much params\n", -1));
		if ((op_tab[i].args[j] == T_REG || op_tab[i].args[j] == T_REG + T_DIR
					|| op_tab[i].args[j] == T_REG + T_IND
					|| op_tab[i].args[j] == T_REG + T_IND + T_DIR)
				&& check_t_reg(tmp[j]) == 1)
			count = count + 1;
		else
			count = check_params_b(tmp, ft_init_op_n(i, j, count), op_tab);
		if (count < 0)
			return (-1);
		j++;
	}
	if (j != op_tab[i].nb_arg)
		return (return_f("FATAL ERROR - too few arguments\n", -1));
	return (count);
}

int			check_line_instruc(char *line, t_op *op_tab)
{
	char	**tmp;
	char	**pmt;
	int		count;
	int		i;
	int		len;

	count = 0;
	i = 0;
	tmp = ft_strsplit(line, ' ');
	while (op_tab[i].nb_arg != 0 && (ft_strcmp(tmp[0], op_tab[i].name) != 0))
		i++;
	if ((i > 15 || tmp[1] == NULL) && free_tab(tmp))
		return (return_f("FATAL ERROR - opcode unknown\n", -1));
	len = ft_strlen(tmp[1]);
	if (tmp[1][len - 1] == ',' && free_tab(tmp))
		return (return_f("FATAL ERROR - there is a final coma\n", -1));
	pmt = ft_strsplit(tmp[1], SEPARATOR_CHAR);
	free_tab(tmp);
	if ((count = check_params(pmt, i, op_tab)) < 0 && free_tab(pmt))
		return (-1);
	free_tab(pmt);
	count++;
	if (op_tab[i].nb_arg > 1)
		count++;
	return (count);
}

int			check_instruc(int fd, t_asm *assm, t_op *op_tab)
{
	char	*line;
	char	*str;
	int		r;

	r = 0;
	while (get_next_line(fd, &line) > 0)
	{
		assm->line_error++;
		if ((str = suppr_space_label(line, assm, 0)) == NULL && f_l(&line))
			return (return_f("FATAL ERROR - wrong syntax line\n", -1));
		if (ft_strcmp("\0", str) == 0)
			;
		else
		{
			if ((r = check_line_instruc(str, op_tab)) < 0 && f_l(&str)
					&& f_l(&line))
				return (-1);
			assm->len_bytes = assm->len_bytes + r;
			free(str);
		}
		free(line);
	}
	if (assm->len_bytes == 0)
		return (return_f("FATAL ERROR - no instructions\n", -1));
	return (assm->len_bytes);
}
