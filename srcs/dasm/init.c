#include "../../includes/dasm.h"

char	**init_tab(void)
{
	char	**tab;
	int	nb;
	int	i;

	nb = PROG_NAME_LENGTH + COMMENT_LENGTH + (CHAMP_MAX_SIZE / 2);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb + 1))))
		return (NULL);
	tab[nb] = NULL;
	if (!(tab[0] = (char *)malloc(sizeof(char) * (PROG_NAME_LENGTH + 1))))
		return (NULL);
	tab[0][PROG_NAME_LENGTH] = '\0';
	if (!(tab[1] = (char *)malloc(sizeof(char) * (COMMENT_LENGTH + 1))))
		return (NULL);
	tab[1][COMMENT_LENGTH] = '\0';
	i = 2;
	while (i < nb)
	{
		if (!(tab[i] = (char *)malloc(sizeof(char) * (41))))
			return (NULL);
		tab[i][40] = '\0';
		i++;
	}
	return (tab);
}

void	init_buffer(t_dasm *dasm)
{
	int	r;

	r = dasm->ret;
	while (r < COMMENT_LENGTH + PROG_NAME_LENGTH + CHAMP_MAX_SIZE + 17)
	{
		dasm->buf[r] = 0;
		r++;
	}
}
