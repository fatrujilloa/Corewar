#include "../../includes/asm.h"

static char	*check_label(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			;
		else if (line[i] == COMMENT_CHAR)
			return ("\0");
		else if (ft_strchr(LABEL_CHARS, line[i]) != NULL)
		{
			while (ft_strchr(LABEL_CHARS, line[i]) != NULL)
				i++;
			if (line[i] == LABEL_CHAR)
			{
				line = line + i + 1;
				i = -1;
			}
			else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
					|| line[i] == '-' || line[i] == DIRECT_CHAR)
				return (suppr_space(line, i));
			else
				return (NULL);
		}
		else
			return (NULL);
		i++;
	}
	return ("\0");
}

static int	check_params_label(char **tmp, int i, t_asm *assm)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (tmp[j] != NULL)
	{
		if (j + 1 > op_tab[i].nb_arg)
			return (-1);
		if ((op_tab[i].args[j] == T_REG || op_tab[i].args[j] == T_REG + T_DIR || op_tab[i].args[j] == T_REG + T_IND || op_tab[i].args[j] == T_REG + T_IND + T_DIR) && check_t_reg(tmp[j]) == 1)
			count = count + 1;
		else if ((op_tab[i].args[j] == T_DIR || op_tab[i].args[j] == T_DIR + T_REG || op_tab[i].args[j] == T_DIR + T_IND || op_tab[i].args[j] == T_DIR + T_REG + T_IND) && check_t_dir_label(tmp[j], assm) == 1)
		{
			if (op_tab[i].label == 0)
				count = count + 4;
			else
				count = count + 2;
		}
		else if ((op_tab[i].args[j] == T_IND || op_tab[i].args[j] == T_IND + T_REG || op_tab[i].args[j] == T_IND + T_DIR || op_tab[i].args[j] == T_IND + T_DIR + T_REG) && check_t_ind_label(tmp[j], assm) == 1)
			count = count + 2;
		else
			return (-1);
		j++;
	}
	return (count);
}

static int	check_label_2(char *line, t_asm *assm)
{
	char	**tmp;
	char	**pmt;
	int	count;
	int	i;

	count = 0;
	i = 0;
	tmp = ft_strsplit(line, ' ');
	while (op_tab[i].nb_arg != 0 && (ft_strcmp(tmp[0], op_tab[i].name) != 0))
		i++;
	if (i > 15)
		return (-1);
	pmt = ft_strsplit(tmp[1], SEPARATOR_CHAR);
	if ((count = check_params_label(pmt, i, assm)) < 0)
		return (-1);
	count++;
	if (op_tab[i].nb_arg > 1)
		count++;
	return (count);
}

int		ft_third_turn(t_asm *assm, char *str)
{
	char	*line;
	int	fd;
	int	r;
	int	r2;

	assm->actual_bytes = 0;
	assm->line_error = 0;
	r = 0;
	while (r < assm->nb_label)
	{
		r2 = 0;
		while (r2 < assm->nb_label)
		{
			if (ft_strcmp(assm->label[r].name, assm->label[r2].name) == 0 && r != r2)
				return (return_f("FATAL ERROR - same label name\n", -1));
			r2++;
		}
		r++;
	}
	if ((fd = open(str, O_RDONLY)) < 3)
	{
		ft_putstr("\033[0;31merror : can't open the file\n\033[0m");
		exit(EXIT_SUCCESS);
	}
	if (check_name(fd, &assm->line_error) < 0 || check_comment(fd, &assm->line_error) < 0)
		return (-1);
	while (get_next_line(fd, &line))
	{
		assm->line_error = assm->line_error + 1;
		if ((line = check_label(line)) == NULL)
			return (return_f("FATAL ERROR - problem with the label\n", -1));
		if (ft_strcmp("\0", line) == 0)
			;
		else
		{
			if ((r = check_label_2(line, assm)) < 0)
				return (return_f("FATAL ERROR - argument call an inexistant label\n", -1));
			assm->actual_bytes = assm->actual_bytes + r;
		}
	}
	close(fd);
	return (0);
}
