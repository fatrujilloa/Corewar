/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_aux_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:48:03 by ftrujill          #+#    #+#             */
/*   Updated: 2020/02/03 00:49:37 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int     ft_check_cor_basics(char *str, int read_count)
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
		exit(ft_print_error("One .cor has size lower than necessary header size"));
	if (read_count > header_size + CHAMP_MAX_SIZE)
		exit(ft_print_error("One .cor content has size greater than maximum size"));
	champ = (t_header *)str;
	return (1);
}

int	ft_check_for_suffix(char *str)
{
	char *suffix;

	if (!str)
		return (0);
	suffix = ft_strrchr(str, '.');
	while (suffix && ft_strlen(suffix + 1) > 3)
		suffix = ft_strrchr(suffix + 1, '.');
	return ((!suffix || strcmp(suffix, ".cor") ? 0 : 1));
}
