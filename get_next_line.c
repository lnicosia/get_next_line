/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:05:31 by lnicosia          #+#    #+#             */
/*   Updated: 2018/11/15 14:42:52 by lnicosia         ###   ########.fr       */
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
	free(tmp);
	ft_strcat(s1, s2);
	return (s1);
}

void		set_data(t_read **current, char **line)
{
	size_t	i;
	char	*final;
	char	*tmp;

	i = 0;
	while ((*current)->str[i] != '\n')
		i++;
	final = ft_strnew(i);
	//ft_putstr("-TOTAL READ: "); ft_putendl((*current)->str);
	ft_strncpy(final, (*current)->str, i);
	*line = final;
	//ft_putstr("-LINE: "); ft_putendl(final);
	if (i < ft_strlen((*current)->str) - 1)
	{
		//ft_putstr("strlen: "); ft_putnbr(ft_strlen(current->str)); ft_putstr(" i: "); ft_putnbr(i); ft_putstr(" last char: \'"); ft_putchar(current->str[i]); ft_putendl("\'");
		tmp = ft_strsub((*current)->str, i + 1, ft_strlen((*current)->str) - i - 1);
		//free(current->str);
		(*current)->str = tmp;
		//free(tmp);
		//ft_putstr("-NEXT READ: "); ft_putstr((*current)->str);
	}
	else
	{
		free((*current)->str);
		(*current)->str = ft_strnew(0);
	}
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*datas = NULL;
	t_read			*current;
	char			buff[BUFF_SIZE + 1];
	int				bytes;
	int				new;

	if ((new =lst_contains(datas, &current, fd)) == 0)
	{
		current = (t_read*)malloc(sizeof(*current));
		current->str = ft_strnew(0);
		current->fd = fd;
		//ft_putstr("-- UNKNOWN FD: "); ft_putnbr(fd); ft_putendl(" --");
		//datas = ft_lstnew(current, sizeof(*current));
		//ft_putendl("NEW NODE CREATED");
	}
	else
	{
		//ft_putstr("-- KNOWN FD: "); ft_putnbr(current->fd); ft_putendl(" --");
		//current = (t_read*)(datas->content);
		//ft_putstr("-FORMER STR: "); ft_putendl(current->str);
		if (ft_strchr(current->str, '\n') != NULL)
		{
			set_data(&current, line);
			return (1);
		}
		//ft_putstr("FORMER STR: "); ft_putendl(current.str);
	}
	while ((bytes = read(fd, buff, BUFF_SIZE)))
	{
		current->str = strealloc(current->str, ft_strlen(current->str), buff, bytes);
		if (ft_strchr(buff, '\n') != NULL)
		{
			set_data(&current, line);
			if (new == 0)
				ft_lstadd(&datas, ft_lstnew(current, sizeof(*current)));
			return (1);
		}
	}
	//ft_putendl("-EOF");
	return (0);
}
