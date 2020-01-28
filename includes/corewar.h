/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:25:55 by rbeaufre          #+#    #+#             */
/*   Updated: 2020/01/27 18:38:35 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H


# include "op.h"
# include "../libft/libft.h"
# include <fcntl.h>

typedef struct s_process	t_process;

typedef struct		s_process
{
	unsigned char	reg[REG_NUMBER][REG_SIZE];
	char			carry;
	int				pc;
	int				wait_until; //Next active cycle
	int				alive;
	t_process		*next;
}					t_process;

typedef struct		s_player
{
	int		nb;
	int		name;
	int		comment;
}					t_player;

typedef struct		s_champ
{
	char	content[CHAMP_MAX_SIZE];
	char	name[PROG_NAME_LENGTH + 4];
	char	comment[COMMENT_LENGTH + 1];
	int		champ_nbr;
	int		champ_size;
	int		champ_position;
}					t_champ;

typedef struct		s_cw
{
	char		arena[MEM_SIZE];
	t_process	*prcs[MAX_PLAYERS];
	t_champ		champ[MAX_PLAYERS];
	int			last_alive;
	int			nb_prcs;
	int			nb_players;
	int			nb_cycles;
	int			nbr_cycles_to_die;
	int			dump_flag;
	int			number_flag;
	int			first_champ_i;
}					t_cw;

typedef struct		s_arg
{
	int				nb_args;	
    unsigned char   type[MAX_ARGS_NUMBER];
    unsigned char   size[MAX_ARGS_NUMBER];
    unsigned char   value[MAX_ARGS_NUMBER][MAX_SIZE];
	unsigned int	int_value[MAX_ARGS_NUMBER];
}					t_arg;

int			ft_display_options(void);
int			ft_print_error(char *str);
int			ft_scan_flags(int argc, char **argv, t_cw *cw);
int			ft_init_cw(t_cw *cw);
int			ft_init_champs(int argc, char **argv, t_cw *cw);
void		ft_init_processes(t_cw *cw);
int			ft_print_hexa(char *str, int size);

#endif
