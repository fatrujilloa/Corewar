/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_turn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:03:48 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 16:19:47 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void		ft_name_label(char *line, t_asm *assm, int *j)
{
	int	i;

	i = 0;
	while (*line == ' ' || *line == '\t' || *line == '\n')
		line++;
	while (ft_strchr(LABEL_CHARS, line[i]) != NULL)
		i++;
	if (!(assm->label[*j].name = (char *)malloc(sizeof(char) * (i + 1))))
		exit(EXIT_SUCCESS);
	assm->label[*j].name[i] = '\0';
	i = 0;
	while (ft_strchr(LABEL_CHARS, line[i]) != NULL)
	{
		assm->label[*j].name[i] = line[i];
		i++;
	}
}

char		*stock_label_b(char *line, int i)
{
	if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
			|| line[i] == '-' || line[i] == DIRECT_CHAR)
		return (suppr_space(line, i));
	return (NULL);
}

char		*stock_label(char *line, t_asm *assm, int *j, int i)
{
	while (line[++i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			;
		else if (line[i] == COMMENT_CHAR)
			return ("\0");
		else if (ft_strchr(LABEL_CHARS, line[i]) != NULL)
		{
			while (ft_strchr(LABEL_CHARS, line[i]) != NULL)
				i++;
			if (line[i] == LABEL_CHAR)
			{
				ft_name_label(line, assm, j);
				assm->label[*j].place = assm->actual_bytes + 1;
				*j = *j + 1;
				line = line + i + 1;
				i = -1;
			}
			else
				return (stock_label_b(line, i));
		}
		else
			return (NULL);
	}
	return ("\0");
}

int			ft_second_turn_b(t_asm *assm, int fd, int i, t_op *op_tab)
{
	char	*line;
	char	*str_2;
	int		r;

	while (get_next_line(fd, &line) > 0)
	{
		assm->line_error = assm->line_error + 1;
		if ((str_2 = stock_label(line, assm, &i, -1)) == NULL && f_l(&line))
			return (return_f("FATAL ERROR - problem with the label\n", -1));
		if (ft_strcmp("\0", str_2) == 0)
			;
		else
		{
			if ((r = check_line_instruc(str_2, op_tab)) < 0 && f_l(&line))
				return (-1);
			free(str_2);
			assm->actual_bytes = assm->actual_bytes + r;
		}
		free(line);
	}
	return (0);
}

int			ft_second_turn(t_asm *assm, char *str, t_op *op_tab)
{
	int	fd;

	assm->actual_bytes = 0;
	assm->line_error = 0;
	if ((fd = open(str, O_RDONLY)) < 3)
	{
		ft_putstr("\033[0;31merror : can't open the file\n\033[0m");
		exit(EXIT_SUCCESS);
	}
	if (!(assm->label = (t_label *)malloc(sizeof(t_label)
			* (assm->nb_label + 1))))
		return (return_f("FATAL ERROR - problem with a malloc\n", -1));
	assm->label[assm->nb_label].name = NULL;
	if (check_name(fd, &assm->line_error) < 0)
		return (-1);
	if (check_comment(fd, &assm->line_error) < 0)
		return (-1);
	if (ft_second_turn_b(assm, fd, 0, op_tab) < 0)
		return (-1);
	close(fd);
	return (0);
}
