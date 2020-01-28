#include "../../includes/asm.h"

static char	*ft_strcat_mal(char *s1, const char *s2)
{
	int	len;
	int	i;
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (i < len && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] && i < (int)ft_strlen(s2))
	{
		str[len + i] = ((char *)s2)[i];
		i++;
	}
	str[len + i] = '\0';
	return (str);
}

char		*suppr_space(char *line, int j)
{
	char	**res;
	char	**res_2;
	char	*str;
	char	*line_b;
	int	i;

	i = 0;
	if (line[j] == '-' || line[j] == '%')
	{	
		if (!(line_b = (char *)malloc(sizeof(char) * (ft_strlen(line) + 2))))
			return (NULL);
		while (i < j)
		{
			line_b[i] = line[i];
			i++;
		}
		line_b[i] = ' ';
		i++;
		while (line[i - 1])
		{
			line_b[i] = line[i - 1];
			i++;
		}
		line_b[i] = '\0';
		line = line_b;
	}
	i = 0;
	res = ft_split_whitespaces(line);
	while (res[i] != NULL)
	{
		if (i == 0)
			str = ft_strcat_mal(res[i], " ");
		else
			str = ft_strcat_mal(str, res[i]);
		i++;
	}
	res_2 = ft_strsplit(str, '#');
	return (res_2[0]);
}

char		*suppr_space_label(char *line, t_asm *assm)
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
			while (line[i] && ft_strchr(LABEL_CHARS, line[i]) != NULL)
				i++;
			if (line[i] && line[i] == LABEL_CHAR)
			{
				assm->nb_label++;
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

int		check_params(char **tmp, int i)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (tmp[j] != NULL)
	{
		if (j + 1 > op_tab[i].nb_arg)
			return (return_f("FATAL ERROR - too much params\n", -1));
		if ((op_tab[i].args[j] == T_REG || op_tab[i].args[j] == T_REG + T_DIR || op_tab[i].args[j] == T_REG + T_IND || op_tab[i].args[j] == T_REG + T_IND + T_DIR) && check_t_reg(tmp[j]) == 1)
			count = count + 1;
		else if ((op_tab[i].args[j] == T_DIR || op_tab[i].args[j] == T_DIR + T_REG || op_tab[i].args[j] == T_DIR + T_IND || op_tab[i].args[j] == T_DIR + T_REG + T_IND) && check_t_dir(tmp[j]) == 1)
		{
			if (op_tab[i].label == 0)
				count = count + 4;
			else
				count = count + 2;
		}
		else if ((op_tab[i].args[j] == T_IND || op_tab[i].args[j] == T_IND + T_REG || op_tab[i].args[j] == T_IND + T_DIR || op_tab[i].args[j] == T_IND + T_DIR + T_REG) && check_t_ind(tmp[j]) == 1)
			count = count + 2;
		else
			return (return_f("FATAL ERROR - an argument does not match with the opcode\n", -1));
		j++;
	}
	if (j != op_tab[i].nb_arg)
		return (return_f("FATAL ERROR - too few arguments\n", -1));
	return (count);
}

int		check_line_instruc(char *line)
{
	char	**tmp;
	char	**pmt;
	int	count;
	int	i;
	int	len;

	count = 0;
	i = 0;
	tmp = ft_strsplit(line, ' ');
	while (op_tab[i].nb_arg != 0 && (ft_strcmp(tmp[0], op_tab[i].name) != 0))
		i++;
	if (i > 15)
		return (return_f("FATAL ERROR - opcode unknown\n", -1));
	len = ft_strlen(tmp[1]);
	if (tmp[1][len - 1] == ',')
		return (return_f("FATAL ERROR - there is a final coma\n", -1));
	pmt = ft_strsplit(tmp[1], SEPARATOR_CHAR);
	if ((count = check_params(pmt, i)) < 0)
		return (-1);
	count++;
	if (op_tab[i].nb_arg > 1)
		count++;
	return (count);
}

int		check_instruc(int fd, t_asm *assm)
{
	char	*line;
	int	r;

	r = 0;
	while (get_next_line(fd, &line))
	{
		assm->line_error++;
		if ((line = suppr_space_label(line, assm)) == NULL)
			return (return_f("FATAL ERROR - wrong syntax line\n", -1));
		if (ft_strcmp("\0", line) == 0)
			;
		else
		{
			if ((r = check_line_instruc(line)) < 0)
				return (-1);
			assm->len_bytes = assm->len_bytes + r;
		}
	}
	if (assm->len_bytes == 0)
		return (return_f("FATAL ERROR - no instructions\n", -1));
	return (assm->len_bytes);
}
