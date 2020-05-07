/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:41:30 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 16:55:19 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

short	f_l(char **line)
{
	free(*line);
	return (1);
}

t_op_n	ft_init_op_n(int i, int j, int count)
{
	t_op_n	op_n;

	op_n.i = i;
	op_n.j = j;
	op_n.count = count;
	return (op_n);
}

int		ft_error(char *str, int fd, int error)
{
	if (error >= 0)
	{
		ft_putstr_fd("\033[0;36m", fd);
		ft_putstr_fd("Problem on line : ", fd);
		ft_putnbr_fd(error, fd);
		ft_putchar_fd('\n', fd);
		ft_putstr_fd("\033[0m", fd);
	}
	ft_putstr_fd("\033[0;33m", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\033[0m", fd);
	return (0);
}

int		return_f(char *str, int return_f)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
	return (return_f);
}

int		ft_error_first_turn(t_asm assm)
{
	if (assm.len_bytes < 0)
		return (ft_error("error : problem on instruct\n", 2, assm.line_error));
	if (assm.len_name < 0)
		return (ft_error("error : problem on name\n", 2, -1));
	if (assm.len_comment < 0)
		return (ft_error("error : problem on comment\n", 2, -1));
	if (assm.len_name > PROG_NAME_LENGTH)
	{
		return_f("FATAL ERROR - name too big\n", 0);
		return (ft_error("error : name too big\n", 2, -1));
	}
	if (assm.len_comment > COMMENT_LENGTH)
	{
		return_f("FATAL ERROR - comment too big\n", 0);
		return (ft_error("error : comment too big\n", 2, -1));
	}
	return (1);
}
