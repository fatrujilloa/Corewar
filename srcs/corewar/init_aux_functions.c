/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_aux_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:15:53 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/07 02:40:27 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void			ft_organize_players(t_cw *cw, int i)
{
	unsigned int	tmp_nb;

	while (i < cw->nb_players - 1)
	{
		if (cw->champ_nbrs[i] == cw->champ_nbrs[i + 1])
			cw->champ_nbrs[i + 1]++;
		if (cw->champ_nbrs[i] < cw->champ_nbrs[i + 1])
			i++;
		else
		{
			tmp_nb = cw->champ_nbrs[i];
			cw->champ_nbrs[i] = cw->champ_nbrs[i + 1];
			cw->champ_nbrs[i + 1] = tmp_nb;
			tmp_nb = cw->champ[i].size;
			cw->champ[i].size = cw->champ[i + 1].size;
			cw->champ[i + 1].size = tmp_nb;
			ft_strswap(cw->champ[i].content, cw->champ[i + 1].content,
				CHAMP_MAX_SIZE);
			ft_strswap(cw->champ[i].name, cw->champ[i + 1].name,
				PROG_NAME_LENGTH + 4);
			ft_strswap(cw->champ[i].comment, cw->champ[i + 1].comment,
				COMMENT_LENGTH + 1);
			i = 0;
		}
	}
}

void			ft_reverse_champ_nbrs(t_cw *cw)
{
	int			i;
	t_process	*prcs;

	i = cw->nb_players;
	prcs = cw->prcs;
	while (--i >= 0)
	{
		cw->champ_nbrs[i] = 4294967296 - cw->champ_nbrs[i];
		*(unsigned int*)prcs->reg[0] = cw->champ_nbrs[i];
		prcs->champ_nb = cw->champ_nbrs[i];
		ft_strnrev(prcs->reg[0], REG_SIZE);
		prcs = prcs->next;
	}
}

void			ft_init_prcs_value(t_cw *cw, t_process *process, int i)
{
	process->pc = 0 + i * (MEM_SIZE / cw->nb_players);
	process->carry = 0;
	process->wait_until = 0;
	process->alive = 0;
	process->valid_arg = 0;
	process->champ = i;
	process->champ_nb = cw->champ_nbrs[i];
	process->nb = i;
	process->valid_arg = 0;
	process->current_op = 0;
}

int				ft_check_cor_basics(char *str, int read_count)
{
	int				i;
	unsigned char	*buff;
	int				header_size;
	t_header		*champ;

	header_size = 4 + PROG_NAME_LENGTH + 8 + COMMENT_LENGTH + 4;
	buff = (unsigned char*)&str[0];
	i = COREWAR_EXEC_MAGIC;
	if (!((buff[0] == (i >> 24) && buff[1] == ((i >> 16) & 0xff) &&
			buff[2] == ((i >> 8) & 0xff) && buff[3] == (i & 0xff))))
		exit(ft_print_error("One .cor does not have the good magic key"));
	if (read_count < header_size)
		exit(ft_print_error("One .cor has size "
			"lower than necessary header size"));
	if (read_count > header_size + CHAMP_MAX_SIZE)
		exit(ft_print_error("One .cor content has size "
			"greater than maximum size"));
	champ = (t_header *)str;
	return (1);
}

int				ft_check_for_suffix(char *str)
{
	char	*suffix;

	if (!str)
		return (0);
	suffix = ft_strrchr(str, '.');
	while (suffix && ft_strlen(suffix + 1) > 3)
		suffix = ft_strrchr(suffix + 1, '.');
	return ((!suffix || strcmp(suffix, ".cor") ? 0 : 1));
}
