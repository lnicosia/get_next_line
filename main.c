/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:28:08 by lnicosia          #+#    #+#             */
/*   Updated: 2018/11/21 13:54:49 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"

int		get_next_line(const int fd, char **line);

int		main(int argc, char **argv)
{
	int		fd = 0;
	int		i;
	char	**line;
	int		ret;

	i = 1;
	if (argc == 1)
	{
		return (1);
	}
	line = (char**)malloc(sizeof(char*));
	if (!(fd = open(argv[1], O_RDONLY)))
	{
		return (1);
	}
	while (((ret = (get_next_line(fd, line))) == 1))
	{
		//ft_putstr("line: "); 
		ft_putendl(*line);
		ft_strdel(line);
	}
	if (close(fd) == -1)
	{
		return (1);
	}
	return (ret);
}
