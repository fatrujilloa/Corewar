/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:42:52 by rbeaufre          #+#    #+#             */
/*   Updated: 2020/01/28 01:07:31 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int	ft_check_next_is_number(char **argv, int *i)
{
	int j;

	j = 0;
	(*i)++;
	while (argv[*i][j])
	{
		if (!ft_isdigit((int)argv[*i][j]))
			exit(ft_print_error("Need a number after option -dump or -n"));
		j++;
	}
	return (1);
}

static int	ft_check_cor_suffix(char *str)
{
	char *suffix;

	suffix = ft_strrchr(str, '.');
	if (suffix)
	{
		suffix++;
		if (!strcmp(suffix, "cor"))
			return (1);
	}
	return (0);
}

int			ft_scan_flags(int argc, char **argv, t_cw *cw)
{
	int i;

	i = 1;
	cw->dump_flag = -1;
	cw->number_flag = 0;
	while (i < argc && argv[i])
	{
		if (argv[i][0] == '-' && ft_strcmp(argv[i], "-dump") == 0 &&
			i < argc - 1 && ft_check_next_is_number(argv, &i) == 1)
			cw->dump_flag = ft_atoi(argv[i]);
		else if (argv[i][0] == '-' && ft_strcmp(argv[i], "-n") == 0 &&
				i < argc - 2 && ft_check_next_is_number(argv, &i) &&
				ft_check_cor_suffix(argv[i + 1]))
			cw->number_flag = ft_atoi(argv[i]);
		else if (ft_check_cor_suffix(argv[i]))
			return (i);
		else
			exit(ft_print_error("Bad option or champion"));
		i++;
	}
	return (1);
}
