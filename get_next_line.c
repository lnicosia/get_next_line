/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:05:31 by lnicosia          #+#    #+#             */
/*   Updated: 2018/11/14 16:31:04 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

t_list	*lst_contains(t_list *lst, int fd)
{
	t_read *tmp;

	while (lst != NULL)
	{
		tmp = (t_read*)(lst->content);
		if (tmp != NULL)
		{
		if (tmp->fd == fd)
			return (lst);
		}
		lst = lst->next;
	}
	return (NULL);
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

void	set_data(t_read *current, char **line)
{
	size_t	i;
	char	*final;
	char	*tmp;

	i = 0;
	while (current->str[i] != '\n')
		i++;
	current->index = i;
	final = ft_strnew(i);
	ft_putstr("\nTOTAL READ: "); ft_putendl(current->str);
	ft_strncpy(final, current->str, i);
	*line = final;
	tmp = ft_strnew(ft_strlen(current->str));
	ft_strcpy(tmp, current->str + i + 1);
	free(current->str);
	current->str = tmp;
	ft_putstr("LINE: "); ft_putendl(final);
	ft_putstr("NEXT READ: \n"); ft_putendl(current->str);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*datas;
	t_read			*current;
	char			buff[BUFF_SIZE + 1];
	int				bytes;

	datas = ft_lstnew(current, sizeof(*current));
	current = (t_read*)malloc(sizeof(*current));
	if ((datas = lst_contains(datas, fd)) == NULL)
	{
		//ft_putendl("UNKNOWN FD");
		current->str = ft_strnew(0);
		current->fd = fd;
		ft_lstadd(&datas, ft_lstnew(current, sizeof(*current)));
	}
	else
	{
		//ft_putendl("KNOWN FD");
		current = (t_read*)(datas->content);
		//ft_putstr("FORMER STR: "); ft_putendl(current.str);
	}
	while ((bytes = read(fd, buff, BUFF_SIZE)))
	{
		current->str = strealloc(current->str, ft_strlen(current->str), buff, bytes);
		if (ft_strchr(buff, '\n') != NULL)
		{
			set_data(current, line);
			return (1);
		}
	}
	return (0);
}
