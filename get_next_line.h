/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:23:24 by lnicosia          #+#    #+#             */
/*   Updated: 2018/11/14 14:49:56 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# define BUFF_SIZE 1

typedef struct	s_read
{
	int		fd;
	size_t	index;
	char	*str;
}				t_read;

int				get_next_line(const int fd, char **line);

#endif
