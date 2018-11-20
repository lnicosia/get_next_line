/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:05:31 by lnicosia          #+#    #+#             */
/*   Updated: 2018/11/20 16:04:17 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int		lst_contains(t_list *lst, t_read **current, int fd)
{
	while (lst != NULL)
	{
		*current = (t_read*)(lst->content);
		if (*current != NULL)
		{
			if ((*current)->fd == fd)
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
	s1 = ft_strnew(size1 + size2);
	ft_strcpy(s1, tmp);
	ft_strdel(&tmp);
	ft_strcat(s1, s2);
	return (s1);
}

void		set_data(t_read *current, char **line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	//ft_putstr("-TOTAL READ: "); ft_putendl(current->str);
	while ((current->str[i] != '\n') && (current->str[i]))
		i++;
	*line = ft_strnew(i);
	ft_strncpy(*line, current->str, i);
	//ft_putstr("-LINE: "); ft_putendl(*line);
	if (i < ft_strlen(current->str) - 1)
	{
		tmp = current->str;
		current->str = ft_strsub(current->str, i + 1, ft_strlen(current->str) - i - 1);
		ft_strdel(&tmp);
	}
	else
	{
		//ft_putendl("Read just enough.");
		ft_strdel(&(current->str));
		current->str = ft_strnew(0);
	}
}

void	del_elem(int fd, t_list **datas)
{
	t_read *read;
	//t_list *del;
	t_list *tmp;
	//t_list *reader;

	tmp = *datas;
	while (tmp->next != NULL)
	{
		read = (t_read*)tmp->content;
		if (read->fd == fd)
		{
			/*ft_putstr("lst #"); ft_putnbr(fd); ft_putendl(" found. Let's try to free this.");
			del = tmp;
			ft_strdel(&read->str);
			free(tmp->content);
			tmp->content = NULL;
			tmp = tmp->next;
			free(del);
			del = NULL;*/
		}
		tmp = tmp->next;
	}
	free((*datas)->content);
	(*datas)->content = NULL;
	free(*datas);
	*datas = NULL;
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*datas = NULL;
	//t_list			*tmp;
	int				new;
	t_read			*current;
	char			buff[BUFF_SIZE + 1];
	int				bytes;

	//ft_putendl("-- NEW CALL --");
	if (fd < 0 || line == NULL)
		return (-1);
	if ((new = lst_contains(datas, &current, fd)) == 0)
	{
		current = (t_read*)malloc(sizeof(*current));
		current->str = ft_strnew(0);
		current->fd = fd;
		//ft_putstr("-- UNKNOWN FD: "); ft_putnbr(fd); ft_putendl(" --");
	}
	else
	{
		//ft_putstr("-- KNOWN FD: "); ft_putnbr(current->fd); ft_putendl(" --");
		if (ft_strchr(current->str, '\n') != NULL)
		{
			set_data(current, line);
			return (1);
		}
	}
	while ((bytes = read(fd, buff, BUFF_SIZE)))
	{
		if (bytes < 0)
			return (-1);
		current->str = strealloc(current->str, ft_strlen(current->str), buff, bytes);
		//ft_putstr("read: "); ft_putendl(current->str);
		if (ft_strchr(buff, '\n') != NULL)
		{
			set_data(current, line);
			if (new == 0)
				ft_lstadd(&datas, ft_lstnew(current, sizeof(*current)));
			return (1);
		}
	}
	if (current->str[0])
	{
		//ft_putendl("-EOF: ");
		set_data(current, line);
		if (new == 0)
			ft_lstadd(&datas, ft_lstnew(current, sizeof(*current)));
		return (1);
	}
	ft_putstr("-- FD "); ft_putnbr(fd); ft_putendl(" read --");
	del_elem(fd, &datas);
	return (0);
}
