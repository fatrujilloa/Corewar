/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 13:47:14 by rbeaufre          #+#    #+#             */
/*   Updated: 2020/01/28 01:11:11 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int	ft_check_cor_basics(char *str, int read_count)
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
	/*
	ft_printf("size of t_header vaut %i\n", sizeof(t_header));
	ft_printf("header size vaut %i\n", header_size);
	ft_printf("read count vaut %i\n", read_count);
	ft_printf("champ prog size vaut %i\n", champ->prog_size);
	ft_printf("read_count - header_size vaut %i\n", read_count - header_size);
	ft_printf("%i\n", buff[4 + PROG_NAME_LENGTH + 8 - 1]);
	ft_printf("%02x\n", buff[4 + PROG_NAME_LENGTH + 8 - 0]);
	ft_printf("%02x\n", buff[4 + PROG_NAME_LENGTH + 8 + 1]);
	*/
	// BREF ICI il faut comparer les 4 bits, ici 00 00 00 17 donc 23 a la taille effetive pour verifier la coherence
	//if (champ->prog_size != (unsigned int)(read_count - header_size))
	//	exit(ft_print_error("One .cor incoherent content size with declaration"));
	return (1);
}

static int	ft_create_champ(char *str, t_cw *cw, int player_nbr)
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
	ft_check_cor_basics(buff, read_count);
	ft_memcpy(((cw->champ)[player_nbr]).name, buff + 4, PROG_NAME_LENGTH);
	ft_memcpy(((cw->champ)[player_nbr]).comment, buff + 4 + PROG_NAME_LENGTH + 8, COMMENT_LENGTH);
	ft_memcpy(((cw->champ)[player_nbr]).content, buff + sizeof(t_header), read_count - sizeof(t_header));
	if (close(fd) == -1)
		exit(ft_print_error("Closing failure"));
	return (1);
}

int			ft_init_champs(int argc, char **argv, t_cw *cw)
{
	int	player_count;
	int	i;

	i = cw->first_champ_i;
	player_count = 0;
	while (i < argc && argv[i])
	{
		if (ft_strcmp(argv[i], "-n") == 0)
			ft_printf("Attention aux -n apres\n");
		ft_create_champ(argv[i], cw, player_count);
		i++;
		player_count++;
		if (player_count > MAX_PLAYERS)
			exit(ft_print_error("Too many players"));
	}
	return (player_count);
}
