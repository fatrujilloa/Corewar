/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:19:30 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/06 20:22:10 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_err_no_player(void)
{
	ft_printf("Need players as arguments\n");
	return (1);
}

int		ft_cor_suffix_ok(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_strstr(argv[i], ".cor") == NULL)
		{
			ft_printf("All files need to be in .cor format \n");
			return (0);
		}
		i++;
	}
	return (1);
}

int		ft_one_point(int argc, char **argv)
{
	int i;
	int j;
	int count;

	i = 1;
	while (i < argc)
	{
		j = 0;
		count = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '.')
				count++;
			j++;
		}
		if (count != 1)
		{
			ft_printf("All files need to be have only one point in their "
				"name \n");
			return (0);
		}
		i++;
	}
	return (1);
}

int		ft_open_size(int argc, char **argv)
{
	int fd;
	int i;
	int size;

	i = 1;
	while (i < argc)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			ft_printf("Error reading file %s\n", argv[i]);
			return (0);
		}
		size = lseek(fd, 0, SEEK_END);
		if (size - 2180 > CHAMP_MAX_SIZE)
		{
			ft_printf("Champion file %s is too big, reduce to %i bytes max\n",
				argv[i], CHAMP_MAX_SIZE);
			return (0);
		}
		close(fd);
		i++;
	}
	return (1);
}

int		ft_check_initial_errors(int argc, char **argv)
{
	if (argc < 2 && ft_err_no_player())
		return (0);
	if (argc > (1 + MAX_PLAYERS))
	{
		ft_printf("Too many players as arguments, Max is %i\n", MAX_PLAYERS);
		return (0);
	}
	if (ft_cor_suffix_ok(argc, argv) == 0)
		return (0);
	return (1);
}
