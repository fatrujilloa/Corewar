#include "../../includes/dasm.h"

unsigned long	puissance(unsigned long nb, int p)
{
	unsigned long	nb_f;

	nb_f = nb;
	if (p == 0)
		return (1);
	while (p > 1)
	{
		nb_f = nb_f * nb;
		p--;
	}
	return (nb_f);
}

int	write_opcode(t_dasm *dasm, int opcode)
{
	int	i;

	i = 0;
	while (op_tab[opcode - 1].name[i])
	{
		dasm->tab[dasm->nb_tab][i] = op_tab[opcode - 1].name[i];
		i++;
	}
	dasm->tab[dasm->nb_tab][i] = ' ';
	return (i + 1);
}

int	write_big_arg(t_dasm *dasm, unsigned int nb_i, int opcode, int j, int i)
{
	int	pass;
	int	inst;

	pass = 0;
	i = i + 2;
	while (nb_i > 0)
	{
		if (pass > 0)
		{
			dasm->tab[dasm->nb_tab][j] = SEPARATOR_CHAR;
			j++;
		}
		inst = nb_i / puissance(2, (6 - (pass * 2)));
		nb_i = nb_i - (inst * puissance(2, (6 - (pass * 2))));
		if (inst == 1)
		{
			if (op_tab[opcode - 1].args[pass] != T_REG && op_tab[opcode - 1].args[pass] != T_REG + T_DIR && op_tab[opcode - 1].args[pass] != T_REG + T_IND && op_tab[opcode - 1].args[pass] != T_REG + T_IND + T_DIR)
				return (-1);
			j = write_reg(dasm, j, i);
			i = i + 1;
		}
		else if (inst == 3)
		{
			if (op_tab[opcode - 1].args[pass] != T_IND && op_tab[opcode - 1].args[pass] != T_IND + T_REG && op_tab[opcode - 1].args[pass] != T_IND + T_DIR && op_tab[opcode - 1].args[pass] != T_IND + T_DIR + T_REG)
				return (-1);
			j = write_ind(dasm, j, i);
			i = i + 2;
		}
		else if (inst == 2)
		{
			if (op_tab[opcode - 1].args[pass] != T_DIR && op_tab[opcode - 1].args[pass] != T_DIR + T_REG && op_tab[opcode - 1].args[pass] != T_DIR + T_IND && op_tab[opcode - 1].args[pass] != T_DIR + T_REG + T_IND)
				return (-1);
			j = write_dir(dasm, j, i, opcode);
			if (op_tab[opcode - 1].label == 1)
				i = i + 2;
			else
				i = i + 4;
		}
		else
			return (-1);
		pass++;
	}
	return (i);
}

int	write_small_arg(t_dasm *dasm, int opcode, int j, int i)
{
	if (op_tab[opcode - 1].args[0] == 1)
	{
		write_reg(dasm, j, i + 1);
		return (1);
	}
	else if (op_tab[opcode - 1].args[0] == 2)
	{
		write_dir(dasm, j, i + 1, opcode);
		if (op_tab[opcode - 1].label == 1)
			return (2);
		return (4);
	}
	else if (op_tab[opcode - 1].args[0] == 3)
	{
		write_ind(dasm, j, i + 1);
		return (2);
	}
	return (-1);
}

int	instruct_alone(t_dasm *dasm, int i)
{
	int		j;
	int		nb;
	unsigned int	nb_inst;
	int		opcode;

	j = 0;
	nb_inst = dasm->buf[i + 1];
	opcode = dasm->buf[i];
	if (opcode < 1 || opcode > 16
			|| (nb_inst < 1 && op_tab[opcode - 1].nb_arg != 1))
		return (return_f("FATAL ERROR : unknown opcode\n", -1));
	j = write_opcode(dasm, opcode);
	if (op_tab[opcode - 1].nb_arg > 1)
	{
		if ((nb = write_big_arg(dasm, nb_inst, opcode, j, i)) == -1)
			return (return_f("FATAL ERROR : pb instuct\n", -1));
		i = nb;
	}
	else
	{
		if ((nb = write_small_arg(dasm, opcode, j, i)) == -1)
			return (return_f("FATAL ERROR : pb instuct\n", -1));
		i = i + nb + 1;
	}
	return (i);
}

int	then(t_dasm *dasm)
{
	int	i;
	int	bis;

	dasm->nb_tab = 2;
	i = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	while (i < dasm->ret)
	{
		if ((bis = instruct_alone(dasm, i)) == -1)
			return (-1);
		i = bis;
		dasm->nb_tab++;
	}
	if (i != dasm->ret)
		return (-1);
	return (0);
}
