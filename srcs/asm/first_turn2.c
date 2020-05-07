/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_turn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:50:26 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 16:45:48 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int			check_name(int fd, int *error)
{
	char	*line;
	int		name;
	int		quote;
	int		len_name;

	name = 0;
	quote = 0;
	len_name = 0;
	while (get_next_line(fd, &line) > 0 && ++(*error))
	{
		if (check_name_b(line, &name, &quote, &len_name) < 0
				&& f_l(&line))
			return (-1);
		free(line);
		if (quote == 2)
			return (len_name);
	}
	return (return_f("FATAL ERROR - wrong syntax name\n", -1));
}

int			check_comment_c(char *line, int *quote, int *len_comment)
{
	int		r;

	if ((r = ft_len_next(line, quote)) < 0)
		return (return_f("FATAL ERROR - wrong syntax name\n", -1));
	*len_comment = *len_comment + r;
	if (*quote == 1)
		*len_comment = *len_comment + 1;
	else if (*quote == 2)
		return (*len_comment);
	return (1);
}

int			check_comment_b(char *line, int *comment, int *quote, int *len_c)
{
	char	*str;

	if (*comment == 0 && (str = ft_strstr(line, COMMENT_CMD_STRING)))
	{
		*comment = *comment + 1;
		if (check_nothing_before(line, COMMENT_CMD_STRING, 0) == 0)
			return (return_f("FATAL ERROR - wrong syntax comment\n", -1));
		if ((*len_c = ft_len_begin(str, COMMENT_CMD_STRING, quote)) < 0)
			return (return_f("FATAL ERROR - wrong syntax comment\n", -1));
		if (*quote == 1)
			*len_c = *len_c + 1;
		if (*quote == 2)
			return (*len_c);
	}
	else if (*comment == 0 && ft_strstr(line, COMMENT_CMD_STRING) == NULL)
	{
		if (check_nothing(line) == 0)
			return (return_f("FATAL_ERROR - wrong syntax on a line\n", -1));
	}
	else
		return (check_comment_c(line, quote, len_c));
	return (1);
}

int			check_comment(int fd, int *error)
{
	char	*line;
	int		comment;
	int		quote;
	int		len_comment;

	comment = 0;
	quote = 0;
	len_comment = 0;
	while (get_next_line(fd, &line) > 0 && ++(*error))
	{
		if (check_comment_b(line, &comment, &quote, &len_comment) < 0
				&& f_l(&line))
			return (-1);
		free(line);
		if (quote == 2)
			return (len_comment);
	}
	return (return_f("FATAL ERROR - wrong syntax comment\n", -1));
}

t_asm		first_turn(char *str, t_asm assm, t_op *op_tab)
{
	int		fd;

	assm.nb_label = 0;
	assm.len_bytes = 0;
	assm.line_error = 0;
	if ((fd = open(str, O_RDONLY)) < 3)
	{
		ft_putstr("\033[0;31merror : can't open the file\033[0m\n");
		exit(EXIT_SUCCESS);
	}
	if ((assm.len_name = check_name(fd, &assm.line_error)) < 0)
		return (assm);
	if ((assm.len_comment = check_comment(fd, &assm.line_error)) < 0)
		return (assm);
	if ((assm.len_bytes = check_instruc(fd, &assm, op_tab)) < 0)
		return (assm);
	close(fd);
	return (assm);
}
