/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:05:31 by lnicosia          #+#    #+#             */
/*   Updated: 2018/11/14 14:47:11 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

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

	i = 0;
	while (current->str[i] != '\n')
		i++;
	current->index = i;
	final = ft_strnew(i);
	ft_strncpy(final, current->str, i);
	*line = final;
	ft_putendl(final);
}

int		get_next_line(const int fd, char **line)
{
	//static t_list	*datas;
	t_read			current;
	char			buff[BUFF_SIZE + 1];
	int				bytes;

	//datas = ft_lstnew(&current, sizeof(current));
	current.str = ft_strnew(0);
	current.fd = fd;
	while (!(bytes = read(fd, buff, BUFF_SIZE)))
	{
		current.str = strealloc(current.str, ft_strlen(current.str), buff, bytes);
		if (ft_strchr(buff, '\n') != NULL)
		{
			set_data(&current, line);
			return (1);
		}
		else
		{
			buff[bytes] = '\0';
		}
	}
	return (0);
}
