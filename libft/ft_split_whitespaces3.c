/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:14:44 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/07/09 17:10:30 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_free_if_error(int nbr, char **res)
{
	while (nbr >= 0)
	{
		if (res[nbr] != NULL)
			free(res[nbr]);
		nbr--;
	}
	free(res);
}

static int		ft_nbr_words(char const *s)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		else if (s[i] < 32 || s[i] > 126)
			return (0);
		else
		{
			nbr++;
			while (s[i] && (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'))
				i++;
		}
	}
	return (nbr);
}

static int		ft_allocate_words(char const *s, char **res)
{
	int i;
	int nbr;
	int size;

	i = 0;
	nbr = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		else
		{
			size = 0;
			while (s[i] && (s[i++] != ' ' && s[i] != '\t' && s[i] != '\n'))
				size++;
			res[nbr] = NULL;
			if (!(res[nbr] = (char*)malloc(sizeof(*s) * size + 1)))
			{
				ft_free_if_error(nbr, res);
				return (0);
			}
			nbr++;
		}
	}
	return (1);
}

static void		ft_fill_res(char const *s, char **res)
{
	int i;
	int nbr;
	int size;

	i = 0;
	nbr = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		else
		{
			size = 0;
			while (s[i] && (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'))
			{
				res[nbr][size] = s[i];
				size++;
				i++;
			}
			res[nbr][size] = '\0';
			nbr++;
		}
	}
}

char			**ft_split_whitespaces(char const *s)
{
	int		words;
	char	**res;

	if (s == NULL)
	{
		if (!(res = (char**)malloc(sizeof(char*))))
			return (0);
		res[0] = 0;
		return (res);
	}
	words = ft_nbr_words(s);
	if (!(res = (char**)malloc(sizeof(char*) * (words + 1))))
		return (0);
	ft_allocate_words(s, res);
	ft_fill_res(s, res);
	res[words] = NULL;
	return (res);
}
