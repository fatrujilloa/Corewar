/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 18:27:13 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/06 18:28:23 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

char	*ft_spaces(unsigned int n)
{
	if (n < 10)
		return ("    ");
	if (n < 100)
		return ("   ");
	if (n < 1000)
		return ("  ");
	else
		return (" ");
}

void	ft_print_op(t_process *prcs, t_arg arg, t_op op)
{
	int	i;

	ft_printf("P%s%u | %s ", ft_spaces(prcs->nb + 1), prcs->nb + 1, op.name);
	i = -1;
	while (++i < arg.nb_args)
	{
		ft_printf("%s%d", arg.size[i] == 1 ? "r" : "", arg.size[i] == 1
		? (int)arg.intv[i] : (int)arg.real_value[i]);
		if (i < arg.nb_args - 1)
			ft_printf(" ");
		else
			ft_printf("\n");
	}
}

void	ft_print_arena(t_cw *cw)
{
	int s;
	int i;

	s = 0;
	while (s * s < MEM_SIZE)
		s++;
	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%02x ", (unsigned char)cw->arena[i]);
		i++;
		if (i % s == 0)
			ft_putchar('\n');
	}
}

int		ft_print_error(char *str)
{
	char c;

	c = '\n';
	write(2, "Error output: ", 14);
	write(2, str, ft_strlen(str));
	write(2, &c, 1);
	return (1);
}

int		ft_error_cw(int n, t_cw *cw)
{
	write(2, "Error output: ", 14);
	if (n == 1)
		ft_printf("Dump number must be a unsigned integer");
	else if (n == 2)
		ft_printf("Champion numbers must be unsigned integers");
	else if (n == 3)
		ft_printf("Champions names must end by .cor");
	else if (n == 4)
		ft_printf("Too many players. MAX_PLAYERS = %d", MAX_PLAYERS);
	else if (n == 5)
		ft_printf("Error output: The position of the #%d champion"
			" must be between 0 and UMAX_INT (4294967295) - #Players (%d)"
			"+ %d", cw->player_count, cw->nb_players, cw->player_count);
	else if (n == 6)
		ft_printf("");
	else if (n == 7)
		ft_printf("");
	else if (n == 8)
		ft_printf("");
	return (1);
}
