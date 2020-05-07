/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:16:53 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/07 02:40:19 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void			ft_create_champ(char *str, t_cw *cw, unsigned int player_count,
							unsigned int champ_nbr)
{
	int		fd;
	int		read_count;
	char	buff[sizeof(t_header) + CHAMP_MAX_SIZE + 1];

	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit(ft_print_error("Opening failure"));
	read_count = read(fd, &buff, sizeof(t_header) + CHAMP_MAX_SIZE + 1);
	if (read_count == -1 || read_count < (int)(sizeof(t_header) + 1))
		exit(ft_print_error("Reading failure"));
	buff[sizeof(t_header) + CHAMP_MAX_SIZE] = 0;
	cw->champ_nbrs[player_count] = champ_nbr;
	cw->champ[player_count].size = read_count - sizeof(t_header);
	ft_check_cor_basics(buff, read_count);
	ft_bzero(cw->champ[player_count].content, CHAMP_MAX_SIZE);
	ft_bzero(cw->champ[player_count].name, PROG_NAME_LENGTH + 4);
	ft_bzero(cw->champ[player_count].comment, COMMENT_LENGTH + 1);
	ft_memcpy(((cw->champ)[player_count]).name, buff + 4, PROG_NAME_LENGTH);
	ft_memcpy(((cw->champ)[player_count]).comment, buff + 4 +
		PROG_NAME_LENGTH + 8, COMMENT_LENGTH);
	ft_memcpy(((cw->champ)[player_count]).content, buff + sizeof(t_header),
		read_count - sizeof(t_header));
	if (close(fd) == -1)
		exit(ft_print_error("Closing failure"));
}

void			ft_init_processes(t_cw *cw)
{
	int			i;
	int			j;
	t_process	*process;

	i = cw->nb_players;
	cw->prcs = (t_process*)ft_memalloc(sizeof(t_process));
	cw->head = &cw->prcs;
	process = cw->prcs;
	while (--i >= 0)
	{
		ft_init_prcs_value(cw, process, i);
		j = -1;
		while (++j < REG_NUMBER)
			ft_bzero(process->reg[j], REG_SIZE);
		*(unsigned int*)process->reg[0] = cw->champ_nbrs[i];
		ft_strnrev(process->reg[0], REG_SIZE);
		ft_init_arg(&process->arg, 0);
		if (i == 0)
			process->next = NULL;
		else if (!(process->next = (t_process*)ft_memalloc(sizeof(t_process))))
			exit(ft_printf("Malloc error"));
		process = process->next;
	}
	ft_reverse_champ_nbrs(cw);
}

void			ft_stock_input(char **argv, t_cw *cw)
{
	int				i;
	unsigned int	champ_nb;

	i = 0;
	while (argv[++i])
	{
		if (ft_strcmp(argv[i], "-v") == 0)
			cw->v_flag = 1;
		else if (ft_strcmp(argv[i], "-dump") == 0)
		{
			cw->dump = ft_mod_atoi(argv[++i]);
			cw->dump_flag = 1;
		}
		else if (ft_strcmp(argv[i], "-n") == 0)
			if ((champ_nb = ((unsigned int)ft_mod_atoi(argv[++i]))) <=
				4294967295 - cw->nb_players + cw->player_count + 1)
				ft_create_champ(argv[++i], cw, cw->player_count++, champ_nb);
			else
				exit(ft_error_cw(5, cw));
		else if (cw->player_count++ == 0)
			ft_create_champ(argv[i], cw, cw->player_count - 1, 1);
		else
			ft_create_champ(argv[i], cw, cw->player_count - 1,
				cw->champ_nbrs[cw->player_count - 2] + 1);
	}
}

void			ft_check_input(char **argv, t_cw *cw)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (ft_strcmp(argv[i], "-v") == 0)
			continue ;
		if (ft_strcmp(argv[i], "-dump") == 0)
		{
			if (!ft_isstrnum(argv[++i]) || ft_mod_atoi(argv[i]) == -1)
				exit(ft_error_cw(1, cw));
			continue ;
		}
		else if (ft_strcmp(argv[i], "-n") == 0)
		{
			if (!ft_isstrnum(argv[++i]) || ft_mod_atoi(argv[i]) == -1)
				exit(ft_error_cw(2, cw));
			else if (!ft_check_for_suffix(argv[++i]))
				exit(ft_error_cw(3, cw));
		}
		else if (!ft_check_for_suffix(argv[i]))
			exit(ft_error_cw(3, cw));
		if (++cw->nb_players > MAX_PLAYERS)
			exit(ft_error_cw(4, cw));
	}
}

int				ft_init_corewar(char **argv, t_cw *cw, int i)
{
	cw->nb_players = 0;
	ft_check_input(argv, cw);
	cw->dump = 0;
	cw->dump_flag = 0;
	cw->v_flag = 0;
	cw->player_count = 0;
	ft_stock_input(argv, cw);
	ft_organize_players(cw, 0);
	cw->nb_cycles = 0;
	cw->nbr_cycles_to_die = CYCLE_TO_DIE;
	cw->nb_prcs = cw->nb_players;
	cw->nb_checks = 0;
	cw->last_alive = cw->nb_players - 1;
	cw->live_counter = 0;
	cw->last_prcs = cw->nb_players;
	cw->last_wipe = 0;
	ft_bzero(cw->alive, MAX_PLAYERS);
	ft_bzero(cw->arena, MEM_SIZE);
	while (++i < cw->nb_players)
		ft_memcpy(&(cw->arena[i * (MEM_SIZE / cw->nb_players)]),
			cw->champ[i].content, CHAMP_MAX_SIZE);
	ft_init_processes(cw);
	return (1);
}
