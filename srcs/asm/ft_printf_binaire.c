#include "../../includes/asm.h"

int	write_comment(int fd, t_asm *assm)
{
	char	*line;
	char	*str;
	int	comment;
	int	quote;
	int	i;
	int	len_comment;
	int	r;

	comment = 0;
	quote = 0;
	ft_print_in_actual("0\0", assm, 4);
	ft_print_in_actual(ft_itoa_base(assm->len_bytes, 16), assm, 4);
	while (get_next_line(fd, &line))
	{
		i = 0;
		if (comment == 0 && (str = ft_strstr(line, COMMENT_CMD_STRING)))
		{
			comment++;
			if (check_nothing_before(line, COMMENT_CMD_STRING) == 0)
				return (-1);
			if ((len_comment = ft_write_begin(str, COMMENT_CMD_STRING, &quote, assm)) < 0)
				return (-1);
			if (quote == 1)
			{
				assm->tab[assm->actual_bytes] = '\n';
				assm->actual_bytes++;
				len_comment++;
			}
			if (quote == 2)
			{
				free(line);
				return (len_comment);
			}
		}
		else if (comment == 0 && ft_strstr(line, COMMENT_CMD_STRING) == NULL)
		{
			if (check_nothing(line) == 0)
				return (-1);
		}
		else
		{
			if ((r = ft_write_next(line, &quote, assm)) < 0)
				return (-1);
			len_comment = len_comment + r;
			if (quote == 1)
			{
				assm->tab[assm->actual_bytes] = '\n';
				assm->actual_bytes++;
				len_comment++;
			}
			if (quote == 2)
			{
				free(line);
				return (len_comment);
			}
		}
		free(line);
	}
	return (-1);
}

int	ft_write_next(char *line, int *quote, t_asm *assm)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"' && *quote < 2)
			*quote = *quote + 1;
		else if (*quote == 1)
		{
			assm->tab[assm->actual_bytes] = line[i];
			assm->actual_bytes++;
			len++;
		}
		else if (line[i] == COMMENT_CHAR)
			break;
		else if (*quote != 1 && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (-1);
		i++;
	}
	return (len);
}

int	ft_write_begin(char *line, char *str, int *quote, t_asm *assm)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (str[i] && line[i] == str[i])
		i++;
	while (line[i])
	{
		if (line[i] == '"' && *quote < 2)
			*quote = *quote + 1;
		else if (*quote == 1)
		{
			assm->tab[assm->actual_bytes] = line[i];
			assm->actual_bytes++;
			len++;
		}
		else if (line[i] == COMMENT_CHAR)
			break;
		else if (*quote != 1 && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (-1);
		i++;
	}
	return (len);
}

unsigned char	ft_deci(char c10, char c1)
{
	if (c10 == 'A' || c10 == 'B' || c10 == 'C' || c10 == 'D' || c10 == 'E' || c10 == 'F')
		c10 = c10 - 55;
	else
		c10 = c10 - 48;
	if (c1 == 'A' || c1 == 'B' || c1 == 'C' || c1 == 'D' || c1 == 'E' || c1 == 'F')
		c1 = c1 - 55;
	else
		c1 = c1 - 48;
	return (c10 * 16 + c1);
}

void		ft_print_in_actual(char *str, t_asm *assm, int size)
{
	int	len;
	int	i;

	i = 1;
	len = ft_strlen(str) - 1;
	while (len >= 0)
	{
		if (len - 1 >= 0)
		{
			assm->tab[assm->actual_bytes + size - i] = ft_deci(str[len - 1], str[len]);
			len = len - 2;
		}
		else
		{
			assm->tab[assm->actual_bytes + size - i] = ft_deci('0', str[len]);
			len--;
		}
		i++;
	}
	assm->actual_bytes = assm->actual_bytes + size;
}

int	write_name(int fd, t_asm *assm)
{
	char	*line;
	char	*str;
	int	name;
	int	quote;
	int	i;
	int	len_name;
	int	r;

	name = 0;
	quote = 0;
	ft_print_in_actual(ft_itoa_base(COREWAR_EXEC_MAGIC, 16), assm, 4);
	while (get_next_line(fd, &line))
	{
		i = 0;
		if (name == 0 && (str = ft_strstr(line, NAME_CMD_STRING)))
		{
			name++;
			if (check_nothing_before(line, NAME_CMD_STRING) == 0)
				return (-1);
			if ((len_name = ft_write_begin(str, NAME_CMD_STRING, &quote, assm)) < 0)
				return (-1);
			if (quote == 1)
			{
				assm->tab[assm->actual_bytes] = '\n';
				assm->actual_bytes++;
				len_name++;
			}
			if (quote == 2)
			{
				free(line);
				return (len_name);
			}
		}
		else if (name == 0 && ft_strstr(line, NAME_CMD_STRING) == NULL)
		{
			if (check_nothing(line) == 0)
				return (-1);
		}
		else
		{
			if ((r = ft_write_next(line, &quote, assm)) < 0)
				return (-1);
			len_name = len_name + r;
			if (quote == 1)
			{
				assm->tab[assm->actual_bytes] = '\n';
				assm->actual_bytes++;
				len_name++;
			}
			if (quote == 2)
			{
				free(line);
				return (len_name);
			}
		}
		free(line);
	}
	return (-1);
}

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

void		ft_char_argu(char **tmp, int i, t_asm *assm)
{
	int	j;
	int	count;

	count = 0;
	j = 0;
	while (j < op_tab[i].nb_arg)
	{
		if (check_t_reg(tmp[j]) == 1)
			count = count + puissance(2, (6 - 2 * j));
		else if (check_t_dir(tmp[j]) == 1)
			count = count + puissance(2, (7 - 2 * j));
		else
		{
			count = count + puissance(2, (6 - 2 * j));
			count = count + puissance(2, (7 - 2 * j));
		}
		j++;
	}
	assm->tab[assm->actual_bytes] = count;
	assm->actual_bytes++;
}

int		print_t_reg(char *str, t_asm *assm)
{
	if (*str != 'r')
		return (-1);
	str++;
	if (ft_str_isdigit(str) == 0)
		return (-1);
	assm->tab[assm->actual_bytes] = ft_atoi(str);
	assm->actual_bytes++;
	return (1);
}

int	print_t_dir(char *str, t_asm *assm, int j)
{
	int i;

	i = 0;
	if (*str != DIRECT_CHAR)
		return (-1);
	str++;
	if (*str == LABEL_CHAR)
	{
		str++;
		while (ft_strcmp(str, assm->label[i].name) != 0)
                        i++;
		if (op_tab[j].label == 0)
		{
			if (assm->label[i].place + PROG_NAME_LENGTH + COMMENT_LENGTH + 16 - assm->actual_bytes_l >= 0)
                                print_nb_bytes(4, assm, assm->label[i].place + PROG_NAME_LENGTH + COMMENT_LENGTH + 16 - assm->actual_bytes_l);
			else
                                print_nb_bytes(4, assm, puissance(16, 8) + (assm->label[i].place + PROG_NAME_LENGTH + COMMENT_LENGTH + 16 - assm->actual_bytes_l));
		}
		else
		{
			if (assm->label[i].place + PROG_NAME_LENGTH + COMMENT_LENGTH + 16 - assm->actual_bytes_l >= 0)
                        	print_nb_bytes(2, assm, assm->label[i].place + PROG_NAME_LENGTH + COMMENT_LENGTH + 16 - assm->actual_bytes_l);
                	else
               	        	print_nb_bytes(2, assm, 65536 + (assm->label[i].place + PROG_NAME_LENGTH + COMMENT_LENGTH + 16 - assm->actual_bytes_l));
		}
		return (1);
	}
	if (*str == '-')
	{
		str++;
		if (op_tab[j].label == 0)
			print_nb_bytes(4, assm, puissance(16, 8) - ft_atoi(str));
		else
			print_nb_bytes(2, assm, 65536 - ft_atoi(str));
	}
	else
	{
		if (op_tab[j].label == 0)
			print_nb_bytes(4, assm, ft_atoi(str));
		else
			print_nb_bytes(2, assm, ft_atoi(str));
	}
	return (1);
}

int	print_t_ind(char *str, t_asm *assm)
{
	int	i;

	i = 0;
	if (*str == LABEL_CHAR)
	{
		str++;
		while (ft_strcmp(str, assm->label[i].name) != 0)
			i++;
		if (assm->label[i].place + PROG_NAME_LENGTH + COMMENT_LENGTH + 16 - assm->actual_bytes_l >= 0)
			print_nb_bytes(2, assm, assm->label[i].place + PROG_NAME_LENGTH + COMMENT_LENGTH + 16 - assm->actual_bytes_l);
		else
			print_nb_bytes(2, assm, 65536 + (assm->label[i].place + PROG_NAME_LENGTH + COMMENT_LENGTH + 16 - assm->actual_bytes_l));
		return (1);
	}
	if (*str == '-')
	{
		str++;
		print_nb_bytes(2, assm, 65536 - ft_atoi(str));
	}
	else
		print_nb_bytes(2, assm, ft_atoi(str));
	return (1);
}

void	print_nb_bytes(int bytes, t_asm *assm, unsigned int nb)
{
	int	i;
	int	c1;
	int	c10;

	i = 1;
	while (nb > 0 && bytes * 2 - i > 0)
	{
		c10 = nb / (puissance(16, bytes * 2 - i));
                nb = nb - c10 * (puissance(16, bytes * 2 - i));
		c1 = nb / (puissance(16, bytes * 2 - i - 1));
		nb = nb - c1 * (puissance(16, bytes * 2 - i - 1));
		assm->tab[assm->actual_bytes + (i - 1) / 2] = 16 * c10 + c1;
		i = i + 2;
	}
	assm->actual_bytes = assm->actual_bytes + bytes;
}

void		ft_print_params(char **tmp, int i, t_asm *assm)
{
	int	j;
	int	count;

	count = 0;
	j = 0;
	while (j < op_tab[i].nb_arg)
	{
		if (print_t_reg(tmp[j], assm) == 1)
			;
		else if (print_t_dir(tmp[j], assm, i) == 1)
			;
		else if (print_t_ind(tmp[j], assm) == 1)
			;
		j++;
	}
}

int		print_line_instruc(char *line, t_asm *assm)
{
	char	**tmp;
	char	**pmt;
	int	i;

	i = 0;
	tmp = ft_strsplit(line, ' ');
	while (op_tab[i].nb_arg != 0 && (ft_strcmp(tmp[0], op_tab[i].name) != 0))
		i++;
	if (i > 15)
		return (-1);
	assm->tab[assm->actual_bytes] = op_tab[i].opcode;
	assm->actual_bytes++;
	pmt = ft_strsplit(tmp[1], SEPARATOR_CHAR);
	if (op_tab[i].nb_arg > 1)
		ft_char_argu(pmt, i, assm);
	ft_print_params(pmt, i, assm);
	return (0);
}

int		print_instruc(int fd, t_asm *assm)
{
	char	*line;
	int	r;

	r = 0;
	while (get_next_line(fd, &line))
	{
		assm->actual_bytes_l = assm->actual_bytes + 1;
		if ((line = suppr_space_label(line, assm)) == NULL)
			return (-1);
		if (ft_strcmp("\0", line) == 0)
			;
		else
			print_line_instruc(line, assm);
	}
	return (assm->len_bytes);
}

int	ft_print_binaire(t_asm *assm, char *str)
{
	int	fd;

	assm->actual_bytes = 0;
	if ((fd = open(str, O_RDONLY)) < 3)
	{
		ft_putstr("\033[0;31merror : can't open the file\n\033[0m");
		exit(EXIT_SUCCESS);
	}
	write_name(fd, assm);
	assm->actual_bytes = PROG_NAME_LENGTH + 4;
	write_comment(fd, assm);
	assm->actual_bytes = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	print_instruc(fd, assm);
	close(fd);
	return (0);
}
