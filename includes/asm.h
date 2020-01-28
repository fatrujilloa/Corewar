#ifndef ASM_H
# define ASM_H

#include "../libft/libft.h"
#include "op.h"
#include <fcntl.h>

# define OP(index)	op_tab[index]

typedef struct		s_label
{
	int		place;
	char		*name;
}			t_label;

typedef struct		s_asm
{
	unsigned char	*tab;
	char		*file;
	int		fd_file;
	int		len_name;
	int		len_comment;
	int		len_bytes;
	int		actual_bytes;
	int		actual_bytes_l;
	int		nb_label;
	int		line_error;
	t_label		*label;
}			t_asm;

int		ft_error(char *str, int fd, int a);
char		*change_s_cor(char *str);
t_asm		first_turn(char *str, t_asm assm);
int		check_comment(int fd, int *error);
int		check_name(int fd, int *error);
int		check_nothing(char *str);
int		ft_len_begin(char *line, char *str, int *quote);
int		check_nothing_before(char *line, char *str);
int		ft_len_next(char *line, int *quote);
int		check_instruc(int fd, t_asm *assm);
char		*suppr_space_label(char *line, t_asm *assm);
char		*suppr_space(char *line, int i);
int		check_line_instruc(char *line);
int		check_params(char **tmp, int i);
int		check_t_ind(char *str);
int		check_t_dir(char *str);
int		check_t_reg(char *str);
int		ft_str_isdigit(char *str);

void		ft_name_label(char *line, t_asm *assm, int *j);
char		*stock_label(char *line, t_asm *assm, int *j);
int		ft_second_turn(t_asm *assm, char *str);

int		check_t_dir_label(char *str, t_asm *assm);
int		check_t_ind_label(char *str, t_asm *assm);
int		ft_third_turn(t_asm *assm, char *str);
int		ft_print_binaire(t_asm *assm, char *str);

int		write_comment(int fd, t_asm *assm);
int		ft_write_next(char *line, int *quote, t_asm *assm);
int		ft_write_begin(char *line, char *str, int *quote, t_asm *assm);
unsigned char	ft_deci(char c10, char c1);
void		ft_print_in_actual(char *str, t_asm *assm, int size);
int		write_name(int fd, t_asm *assm);
int		print_instruc(int fd, t_asm *assm);

unsigned long	puissance(unsigned long nb, int p);
void		ft_char_argu(char **tmp, int i, t_asm *assm);
int		print_t_reg(char *str, t_asm *assm);
int		print_t_dir(char *str, t_asm *assm, int j);
int		print_t_ind(char *str, t_asm *assm);
void		print_nb_bytes(int bytes, t_asm *assm, unsigned int nb);
void		ft_print_params(char **tmp, int i, t_asm *assm);
int		print_line_instruc(char *line, t_asm *assm);
int		print_instruc(int fd, t_asm *assm);

int		return_f(char *str, int return_f);

#endif
