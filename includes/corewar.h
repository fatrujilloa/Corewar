/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:25:55 by rbeaufre          #+#    #+#             */
/*   Updated: 2020/02/03 23:57:10 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H


# include "op.h"
# include "../libft/libft.h"
# include <fcntl.h>

typedef struct		s_arg
{
	int				nb_args;
	int				total_size;
    unsigned char   type[MAX_ARGS_NUMBER];
    unsigned char   size[MAX_ARGS_NUMBER];
    unsigned char   value[MAX_ARGS_NUMBER][MAX_SIZE];
	unsigned int	int_value[MAX_ARGS_NUMBER];
	unsigned int   	real_value[MAX_ARGS_NUMBER];
}					t_arg;

typedef struct s_process	t_process;

typedef struct		s_process
{
	char			carry;
	char			champ;
	char			alive;
	int				pc;
	unsigned int	nb;
	unsigned char	reg[REG_NUMBER][REG_SIZE];
	unsigned int	champ_nb;
	unsigned int	wait_until; //Next active cycle
	int				valid_arg; /* Takes values: 0 if the encoding byte gives type 00 to one of the arguments.
								-1 if the encoding byte is well defined but the registers in the arguments do not exist ().
								-2 if the encoging byte is well defined, the registers exist but the types do not correspond to what is needed.
								1 if everything is fine. 
								If valid_arg == 1 the operation will be effectuated normally.
								Otherwise the VM waits op.cycle cycles and then moves the PC by the total_size = 2 + size given by encoding byte */
	t_arg			arg;
	t_process		*next;
}					t_process;

/*
typedef struct		s_player
{
	int		nb;
	int		name;
	int		comment;
}					t_player;
*/

typedef struct		s_champ
{
	char			content[CHAMP_MAX_SIZE];
	char			name[PROG_NAME_LENGTH + 4];
	char			comment[COMMENT_LENGTH + 1];
	//unsigned int	nbr;
	unsigned int	size;
	//int		champ_position;
}					t_champ;

typedef struct		s_cw
{
	char			arena[MEM_SIZE];
	t_process		*prcs;
	t_process		**head;
	t_champ			champ[MAX_PLAYERS];
	unsigned int	last_prcs;
	int				last_alive;
	unsigned int	live_counter;
	unsigned int	last_wipe;
	unsigned int	nb_prcs;
	int				nb_players;
	unsigned int	nb_cycles;
	unsigned int	nbr_cycles_to_die;
	unsigned int	dump;
	char			dump_flag;
	//int				number_flag;
	unsigned int	champ_nbrs[MAX_PLAYERS];
	char			alive[MAX_PLAYERS];
}					t_cw;

//int				ft_scan_flags(int argc, char **argv, t_cw *cw);
//int				ft_init_champs(int argc, char **argv, t_cw *cw);

void    		ft_strnrev(unsigned char *str, unsigned int size);
void			ft_get_args(t_cw *cw, t_process *prcs, t_arg *arg, t_op op);
int				ft_check_operation(t_process *prcs, t_op op);
void     		ft_arg_values(t_cw *cw, t_process *prcs, t_arg *arg);
int     		ft_new_prcs(t_process **lst, int new_pc);
unsigned int	ft_str_to_int(unsigned char *str, unsigned int size);
unsigned int    ft_ind_arg(t_cw *cw, int pc);
void			ft_lstdelnext(t_process **lst, t_process **prev);
/*
** Initialize
*/
void			ft_init_processes(t_cw *cw);
int				ft_create_champ(char *str, t_cw *cw, unsigned int player_count,
							unsigned int champ_nbr);
void			ft_init_arg(t_arg *arg, unsigned char nb_args);
int				ft_init_corewar(char** argv, t_cw *cw);
/*
** Print
*/
void			ft_print_prcs(t_process *prcs);
void			ft_print_arena(t_cw *cw);
int				ft_display_options(void);
int				ft_print_error(char *str);
void			ft_print_op(t_process *prcs, t_arg arg, t_op op);
int				ft_print_hexa(char *str, int size);
char   			*ft_spaces(unsigned int n);
/*
** Auxiliar initialize functions
*/
unsigned int	ft_max(unsigned int a, unsigned int b);
long long int	ft_mod_atoi(const char *str);
int				ft_isstrnum(char *str);
int				ft_check_cor_basics(char *str, int read_count);
int				ft_check_for_suffix(char *str);
//void    		ft_strnrev(unsigned char *str, unsigned int size);
/*
** Auxiliar op functions
*/
void    		ft_real_values(t_cw *cw, t_process *prcs, t_arg *arg);
unsigned int    ft_recover_value_arena(t_cw *cw, int pc, int size);
void    		ft_update_process(t_cw *cw, t_process *prcs, t_op op);
int     		ft_new_process(t_cw *cw, t_process **head, t_process *prcs, int new_pc);

#endif
