#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include "op.h"
# include <fcntl.h>

# define OP(index)	op_tab[index]

typedef struct		s_dasm
{
	char		**tab;
	int		nb_tab;
	char		*file;
	unsigned char	buf[COMMENT_LENGTH + PROG_NAME_LENGTH + CHAMP_MAX_SIZE + 17];
	int		ret;
	int		fd;
}			t_dasm;

int			ft_error(char *str, int fd, int error, int r);
int			return_f(char *str, int return_f);
void			free_tab(char **tab);

char			*change_cor_s(char *str);

char			**init_tab(void);
void			init_buffer(t_dasm *dasm);

int			begin(t_dasm *dasm);
int			check_magic_number(t_dasm *dasm);
void			put_name_in_tab(t_dasm *dasm);
int			check_padding(t_dasm *dasm, int place);
void			put_comment_in_tab(t_dasm *dasm);
int			check_number_instruct(t_dasm *dasm);

int			then(t_dasm *dasm);
int			instruct_alone(t_dasm *dasm, int i);
int			write_opcode(t_dasm *dasm, int opcode);
int			write_big_arg(t_dasm *dasm, unsigned int nb_i, int opcode, int j, int i);
int			write_small_arg(t_dasm *dasm, int opcode, int j, int i);

void			ft_putnbr_dasm(int n, t_dasm *dasm, int *j);
int			write_reg(t_dasm *dasm, int j, int i);
int			write_dir(t_dasm *dasm, int j, int i, int opcode);
int			write_ind(t_dasm *dasm, int j, int i);
unsigned long		puissance(unsigned long nb, int p);

#endif
