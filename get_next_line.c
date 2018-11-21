/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:05:31 by lnicosia          #+#    #+#             */
/*   Updated: 2018/11/21 12:33:01 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int		lst_contains(t_list *lst, t_read **curr, int fd)
{
	while (lst != NULL)
	{
		*curr = (t_read*)(lst->content);
		if (*curr != NULL)
		{
			if ((*curr)->fd == fd)
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

char	*strealloc(char *s1, int size1, char *s2, int size2)
{
	char	*tmp;

	tmp = s1;
	s2[size2] = '\0';
	if (!(s1 = ft_strnew(size1 + size2)))
		return (0);
	ft_strcpy(s1, tmp);
	ft_strdel(&tmp);
	ft_strcat(s1, s2);
	return (s1);
}

int		set_data(t_read *curr, char **line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	ft_putstr("Total read: "); ft_putendl(curr->str);
	ft_putstr("len = "); ft_putnbr(ft_strlen(curr->str)); ft_putendl("");
	while ((curr->str[i] != '\n') && (curr->str[i]))
		i++;
	if (!(*line = ft_strnew(i)))
		return (-1);
	ft_strncpy(*line, curr->str, i);
	if (i < ft_strlen(curr->str) - 1)
	{
		tmp = curr->str;
		if (!(curr->str = ft_strsub(curr->str, i + 1,
						ft_strlen(curr->str) - i - 1)))
			return (-1);
		ft_strdel(&tmp);
	}
	else
	{
		ft_strdel(&(curr->str));
		if (!(curr->str = ft_strnew(0)))
			return (-1);
	}
	return (0);
}

int		set_and_add(t_list **datas, char **line, t_read *curr, int new)
{
	t_list *lst;

	if (set_data(curr, line) == -1)
		return (-1);
	if (new == 0)
	{
		if (!(lst = ft_lstnew(curr, sizeof(*curr))))
			return (-1);
		ft_lstadd(datas, lst);
		free(curr);
		curr = NULL;
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*datas = NULL;
	int				new;
	t_read			*curr;
	char			buff[BUFF_SIZE + 1];
	int				ret;

	if (fd < 0 || line == NULL)
		return (-1);
	if ((new = lst_contains(datas, &curr, fd)) == 0)
	{
		if (!(curr = (t_read*)malloc(sizeof(*curr))))
			return (-1);
		if (!(curr->str = ft_strnew(0)))
			return (-1);
		curr->fd = fd;
	}
	while ((!(ft_strchr(curr->str, '\n'))) && (ret = read(fd, buff, BUFF_SIZE)))
	{
		if (ret < 0 || !(curr->str = strealloc(curr->str,
						ft_strlen(curr->str), buff, ret)))
			return (-1);
	}
	if (curr->str[0])
		return (set_and_add(&datas, line, curr, new));
	return (0);
}
