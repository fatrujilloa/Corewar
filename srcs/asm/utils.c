#include "../../includes/asm.h"

int	ft_len_next(char *line, int *quote)
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
			len++;
		else if (line[i] == COMMENT_CHAR)
			break;
		else if (*quote != 1 && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (-1);
		i++;
	}
	return (len);
}

int	ft_len_begin(char *line, char *str, int *quote)
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
			len++;
		else if (line[i] == COMMENT_CHAR)
			break;
		else if (*quote != 1 && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (-1);
		i++;
	}
	return (len);
}

int	check_nothing_before(char *line, char *str)
{
	int	i;

	i = 0;
	while (*line)
	{
		if (str[i] && *line == str[i])
		{
			if (*line == ' ' || *line == '\t' || *line == '\n')
				i++;
			else
			{
				while (str[i] && *line && *line == str[i])
				{
					line = line + 1;
					i++;
				}
				if (!str[i])
					return (1);
				else
					return (0);
			}
		}
		else if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		else if (!str[i])
			return (1);
		line = line + 1;
	}
	return (0);
}

int	check_nothing(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
			return (1);
		if (str[i] != ' ' && str[i] != '\t' && str[i] == '\n')
			return (0);
				i++;
	}
	return (1);
}
