/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:35:11 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 17:54:59 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

void		end_dasm(t_dasm *dasm, t_op *op_tab)
{
	print_dasm(dasm);
	free_tab(dasm->tab);
	free(dasm->file);
	free_op_tab(op_tab);
	close(dasm->fd);
}

int			main(int argc, char **argv)
{
	t_dasm	dasm;
	t_op	*op_tab;

	if (!(op_tab = init_op_tab()))
		return (0);
	if (argc != 2 && free_op_tab(op_tab))
		return (ft_error("usage: ./asm champion.s\n", 2, -1, 0));
	if ((dasm.fd = open(argv[1], O_RDONLY)) < 3 && free_op_tab(op_tab))
		return (ft_error("can't open the file\n", 2, -1, 0));
	if ((dasm.ret = read(dasm.fd, dasm.buf, COMMENT_LENGTH + PROG_NAME_LENGTH
			+ CHAMP_MAX_SIZE + 17)) < 0 && free_op_tab(op_tab))
		return (ft_error("can't read the file\n", 2, -1, 0));
	if (dasm.ret > COMMENT_LENGTH + PROG_NAME_LENGTH + CHAMP_MAX_SIZE + 16
			&& free_op_tab(op_tab))
		return (ft_error("file too big, there is a limit\n", 2, -1, 0));
	init_buffer(&dasm);
	if (!(dasm.file = change_cor_s(argv[1])) && free_op_tab(op_tab))
		return (ft_error("error : your file is incorrect\n", 2, -1, 0));
	dasm.tab = init_tab();
	if (begin(&dasm) == -1 && free_op_tab(op_tab))
		return (ft_error("error : your file is incorrect\n", 2, -1, 0));
	if (then(&dasm, op_tab) == -1 && free_op_tab(op_tab))
		return (ft_error("error : instructions are false\n", 2, -1, 0));
	end_dasm(&dasm, op_tab);
	return (0);
}
