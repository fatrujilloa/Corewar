#include "../../includes/asm.h"

int	check_name(int fd, int *error)
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
	while (get_next_line(fd, &line))
	{
		*error = *error + 1;
		i = 0;
		if (name == 0 && (str = ft_strstr(line, NAME_CMD_STRING)))
		{
			name++;
			if (check_nothing_before(line, NAME_CMD_STRING) == 0)
				return (return_f("FATAL ERROR - wrong syntax name\n", -1));
			if ((len_name = ft_len_begin(str, NAME_CMD_STRING, &quote)) < 0)
				return (return_f("FATAL ERROR - wrong syntax name\n", -1));
			if (quote == 1)
				len_name++;
			if (quote == 2)
			{
				free(line);
				return (len_name);
			}
		}
		else if (name == 0 && ft_strstr(line, NAME_CMD_STRING) == NULL)
		{
			if (check_nothing(line) == 0)
				return (return_f("FATAL_ERROR - wrong syntax on a line\n", -1));
		}
		else
		{
			if ((r = ft_len_next(line, &quote)) < 0)
				return (return_f("FATAL ERROR - wrong syntax name\n", -1));
			len_name = len_name + r;
			if (quote == 1)
				len_name++;
			if (quote == 2)
			{
				free(line);
				return (len_name);
			}
		}
		free(line);
	}
	return (return_f("FATAL ERROR - wrong syntax name\n", -1));
}

int	check_comment(int fd, int *error)
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
	while (get_next_line(fd, &line))
	{
		*error = *error + 1;
		i = 0;
		if (comment == 0 && (str = ft_strstr(line, COMMENT_CMD_STRING)))
		{
			comment++;
			if (check_nothing_before(line, COMMENT_CMD_STRING) == 0)
				return (return_f("FATAL ERROR - wrong syntax comment\n", -1));
			if ((len_comment = ft_len_begin(str, COMMENT_CMD_STRING, &quote)) < 0)
				return (return_f("FATAL ERROR - wrong syntax comment\n", -1));
			if (quote == 1)
				len_comment++;
			if (quote == 2)
			{
				free(line);
				return (len_comment);
			}
		}
		else if (comment == 0 && ft_strstr(line, COMMENT_CMD_STRING) == NULL)
		{
			if (check_nothing(line) == 0)
				return (return_f("FATAL_ERROR - wrong syntax on a line\n", -1));
		}
		else
		{
			if ((r = ft_len_next(line, &quote)) < 0)
				return (return_f("FATAL ERROR - wrong syntax comment\n", -1));
			len_comment = len_comment + r;
			if (quote == 1)
				len_comment++;
			if (quote == 2)
			{
				free(line);
				return (len_comment);
			}
		}
		free(line);
	}
	return (return_f("FATAL ERROR - wrong syntax comment\n", -1));
}

t_asm		first_turn(char *str, t_asm assm)
{
	int	fd;

	assm.nb_label = 0;
	assm.len_bytes = 0;
	assm.line_error = 0;
	if ((fd = open(str, O_RDONLY)) < 3)
	{
		ft_putstr("\033[0;31merror : can't open the file\033[0m\n");
		exit(EXIT_SUCCESS);
	}
	if ((assm.len_name = check_name(fd, &assm.line_error)) < 0)
		return (assm);
	if ((assm.len_comment = check_comment(fd, &assm.line_error)) < 0)
		return (assm);
	if ((assm.len_bytes = check_instruc(fd, &assm)) < 0)
		return (assm);
	close(fd);
	return (assm);
}
