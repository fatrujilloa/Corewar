/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:32:05 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/11/28 21:11:25 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_fd_list	*ft_locate_fd(t_fd_list **files, int fd)
{
	t_fd_list *tmp;
	t_fd_list *new;

	tmp = *files;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(new = (t_fd_list *)malloc(sizeof(t_fd_list))))
		return (0);
	if (!(new->str = (char *)malloc(sizeof(char))))
		return (0);
	(new->str)[0] = '\0';
	new->fd = fd;
	new->next = *files;
	*files = new;
	return (new);
}

static int			ft_bks(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int			ft_allocate_line(char *str, char **line)
{
	int		index;

	if (ft_strlen(str) == 0)
		return (0);
	index = ft_bks(str);
	if (index == -1)
	{
		if (!(*line = ft_strnew(ft_strlen(str))))
			return (-1);
		ft_strncpy(*line, str, ft_strlen(str));
		return (2);
	}
	if (index >= 0)
	{
		if (!(*line = ft_strnew(index)))
			return (-1);
		ft_strncpy(*line, str, index);
		return (1);
	}
	return (-1);
}

static void			ft_swap_free(char **tmp, char *buf, char **str)
{
	*tmp = ft_strjoin(*str, buf);
	free(*str);
	*str = *tmp;
}

int					get_next_line(const int fd, char **line)
{
	static t_fd_list	*files = NULL;
	t_fd_list			*l;
	char				buf[BUFF_SIZE + 1];
	int					ret;
	char				*tmp;

	if (line == NULL || fd < 0 || BUFF_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	l = ft_locate_fd(&files, fd);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		ft_swap_free(&tmp, buf, &(l->str));
		if (ft_bks(l->str) >= 0)
			break ;
	}
	ret = ft_allocate_line(l->str, line);
	if (ret == -1)
		return (-1);
	tmp = ((ret == 1) ? (ft_strsub(l->str, ft_bks(l->str) + 1, \
			ft_strlen(l->str) - ft_bks(l->str))) : ft_strsub(l->str, 0, 0));
	free(l->str);
	l->str = tmp;
	return ((ret == 0) ? 0 : 1);
}
