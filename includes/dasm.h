/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:16:26 by gmoindro          #+#    #+#             */
/*   Updated: 2020/01/17 17:18:39 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H
# define DASM_H

# include "../libft/libft.h"
# include "op.h"
# include <fcntl.h>

# define N_LENGTH PROG_NAME_LENGTH

typedef struct		s_dasm
{
	char			**tab;
	int				nb_tab;
	char			*file;
	unsigned char	buf[COMMENT_LENGTH + N_LENGTH + CHAMP_MAX_SIZE + 17];
	int				ret;
	int				fd;
	int				i;
}					t_dasm;

typedef struct		s_op_n
{
	int				i;
	int				j;
	int				opcode;
}					t_op_n;

int					ft_error(char *str, int fd, int error, int r);
int					return_f(char *str, int return_f);
void				free_tab(char **tab);
char				*change_cor_s(char *str);
char				**init_tab(void);
void				init_buffer(t_dasm *dasm);
int					begin(t_dasm *dasm);
int					check_magic_number(t_dasm *dasm);
void				put_name_in_tab(t_dasm *dasm);
int					check_padding(t_dasm *dasm, int place);
void				put_comment_in_tab(t_dasm *dasm);
int					check_number_instruct(t_dasm *dasm);
int					then(t_dasm *dasm, t_op *op_tab);
int					instruct_alone(t_dasm *dasm, int i, t_op *op_tab);
int					write_opcode(t_dasm *dasm, int opcode, t_op *op_tab);
int					write_big_arg(t_dasm *dasm, unsigned int nb_i,
							t_op_n n, t_op *op_tab);
int					write_small_arg(t_dasm *dasm, t_op_n n, t_op *op_tab);
void				ft_putnbr_dasm(int n, t_dasm *dasm, int *j);
int					write_reg(t_dasm *dasm, int j, int i);
int					write_dir(t_dasm *dasm, int j, int opcode, t_op *op_tab);
int					write_ind(t_dasm *dasm, int j, int i);
unsigned long		puissance(unsigned long nb, int p);
void				ft_putnbr_dasm_b(t_dasm *dasm, int *j);
t_op_n				change_op_n(int i, int j, int opcode);
t_op_n				write_big_a_1(t_op_n n, int pass, t_dasm *dasm,
							t_op *op_tab);
t_op_n				write_big_a_2(t_op_n n, int pass, t_dasm *dasm,
							t_op *op_tab);
t_op_n				write_big_a_3(t_op_n n, int pass, t_dasm *dasm,
							t_op *op_tab);
t_op				*init_op_tab(void);
char				*name_op_tab(char *str);
void				init_op_tab_1(t_op *op_tab);
void				init_op_tab_2(t_op *op_tab);
void				init_op_tab_3(t_op *op_tab);
void				init_op_tab_4(t_op *op_tab);
void				init_op_tab_5(t_op *op_tab);
void				init_op_tab_6(t_op *op_tab);
void				init_op_tab_7(t_op *op_tab);
void				init_op_tab_8(t_op *op_tab);
void				init_op_tab_9(t_op *op_tab);
void				init_op_tab_10(t_op *op_tab);
void				init_op_tab_11(t_op *op_tab);
void				init_op_tab_12(t_op *op_tab);
void				init_op_tab_13(t_op *op_tab);
void				init_op_tab_14(t_op *op_tab);
void				init_op_tab_15(t_op *op_tab);
void				init_op_tab_16(t_op *op_tab);
void				init_op_tab_17(t_op *op_tab);
short				free_op_tab(t_op *op_tab);
void				end_dasm(t_dasm *dasm, t_op *op_tab);
void				print_dasm(t_dasm *dasm);

#endif
