/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:30:36 by gmoindro          #+#    #+#             */
/*   Updated: 2020/01/30 12:31:17 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

int		begin(t_dasm *dasm)
{
	if (check_magic_number(dasm) == -1)
		return (return_f("FATAL ERROR : bad magic number\n", -1));
	put_name_in_tab(dasm);
	if (check_padding(dasm, 4 + PROG_NAME_LENGTH) == -1)
		return (return_f("FATAL ERROR : no padding 1\n", -1));
	if (check_number_instruct(dasm) == -1)
		return (return_f("FATAL ERROR : false number instruct\n", -1));
	put_comment_in_tab(dasm);
	if (check_padding(dasm, 12 + PROG_NAME_LENGTH + COMMENT_LENGTH) == -1)
		return (return_f("FATAL ERROR : no padding 2\n", -1));
	return (0);
}
