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

int				print_instruc(int fd, t_asm *assm, t_op *op_tab)
{
	char	*line;
	char	*str;

	while (get_next_line(fd, &line) > 0)
	{
		assm->actual_bytes_l = assm->actual_bytes + 1;
		if ((str = suppr_space_label(line, assm, 0)) == NULL)
		{
			free(line);
			return (-1);
		}
		if (ft_strcmp("\0", str) == 0)
			;
		else
		{
			print_line_instruc(str, assm, op_tab);
			free(str);
		}
		free(line);
	}
	return (assm->len_bytes);
}

int				ft_print_binaire(t_asm *assm, char *str, t_op *op_tab)
{
	int	fd;

	assm->actual_bytes = 0;
	if ((fd = open(str, O_RDONLY)) < 3)
	{
		ft_putstr("\033[0;31merror : can't open the file\n\033[0m");
		exit(EXIT_SUCCESS);
	}
	write_name(fd, assm);
	assm->actual_bytes = PROG_NAME_LENGTH + 4;
	write_comment(fd, assm);
	assm->actual_bytes = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	print_instruc(fd, assm, op_tab);
	close(fd);
	return (0);
}
