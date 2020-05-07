/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:41:30 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 16:55:19 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	ft_print_in_file(char *file, unsigned char *tab, t_asm assm)
{
	int		h;
	int		fd;

	if ((fd = open(file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 3)
	{
		ft_putstr("\033[0;31merror : can't open the file\n\033[0m");
		exit(EXIT_SUCCESS);
	}
	h = -1;
	ft_putstr("Writing output program to ");
	ft_putstr(file);
	ft_putchar('\n');
	while (++h < PROG_NAME_LENGTH + COMMENT_LENGTH + 16 + assm.len_bytes)
		ft_putchar_fd(tab[h], fd);
	close(fd);
}

void	free_op_tab(t_op *op_tab)
{
	free(op_tab[0].name);
	free(op_tab[1].name);
	free(op_tab[2].name);
	free(op_tab[3].name);
	free(op_tab[4].name);
	free(op_tab[5].name);
	free(op_tab[6].name);
	free(op_tab[7].name);
	free(op_tab[8].name);
	free(op_tab[9].name);
	free(op_tab[10].name);
	free(op_tab[11].name);
	free(op_tab[12].name);
	free(op_tab[13].name);
	free(op_tab[14].name);
	free(op_tab[15].name);
	free(op_tab[16].name);
	free(op_tab);
}

short	free_global(t_asm *assm, t_op *op_tab, int nb)
{
	int		i;

	i = 0;
	free(assm->file);
	free_op_tab(op_tab);
	if (nb > 1)
	{
		while (i < assm->nb_label && assm->label[i].name != NULL)
		{
			free(assm->label[i].name);
			i++;
		}
		free(assm->label);
	}
	if (nb > 2)
		free(assm->tab);
	return (1);
}

void	ft_change_tab_asm(t_asm *assm)
{
	int		i;

	i = -1;
	while (++i < PROG_NAME_LENGTH + COMMENT_LENGTH + 16 + assm->len_bytes)
		assm->tab[i] = '\0';
}

int		main(int argc, char **argv)
{
	t_asm	assm;
	t_op	*o;

	if (!(o = init_op_tab()))
		return (0);
	if (argc != 2)
		return (ft_error("usage: ./asm champion.s\n", 2, -1));
	if (!(assm.file = change_s_cor(argv[1])))
		return (ft_error("error : your file is incorrect\n", 2, -1));
	assm = first_turn(argv[1], assm, o);
	if (ft_error_first_turn(assm) == 0 && free_global(&assm, o, 1))
		return (0);
	if (ft_second_turn(&assm, argv[1], o) < 0 && free_global(&assm, o, 2))
		return (ft_error("error : problem on file\n", 2, assm.line_error));
	if (ft_third_turn(&assm, argv[1], o) < 0 && free_global(&assm, o, 2))
		return (ft_error("error : problem on file\n", 2, assm.line_error));
	if (!(assm.tab = (unsigned char *)malloc(sizeof(unsigned char)
			* (PROG_NAME_LENGTH + COMMENT_LENGTH + 16 + assm.len_bytes)))
				&& free_global(&assm, o, 2))
		return (ft_error("error : probleme de malloc\n", 2, -1));
	ft_change_tab_asm(&assm);
	ft_print_binaire(&assm, argv[1], o);
	ft_print_in_file(assm.file, assm.tab, assm);
	free_global(&assm, o, 3);
	return (0);
}
