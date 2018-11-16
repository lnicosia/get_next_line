/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:28:08 by lnicosia          #+#    #+#             */
/*   Updated: 2018/11/16 15:43:01 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

int		get_next_line(const int fd, char **line);

int		main(int argc, char **argv)
{
	int		fd = 0;
	int		i;
	char	**line;

	i = 1;
	if (argc == 1)
	{
		//ft_putendl("Err NO FILE");
		return (1);
	}
	//ft_putstr("BUFF_SIZE: "); ft_putnbr(BUFF_SIZE); ft_putendl("");
	line = (char**)malloc(sizeof(char*));
	//line = NULL;
	if (!(fd = open(argv[1], O_RDONLY)))
	{
		//ft_putendl("Err OPEN");
		return (1);
	}
	//ft_putendl("OPEN OK");
	while (get_next_line(fd, line) == 1)
	{
		//ft_putnbr(i++); ft_putendl("-");
		ft_putendl(*line);
		ft_strdel(line);
	}
	//get_next_line(fd, line);
	if (close(fd) == -1)
	{
		//ft_putendl("Err CLOSE");
		return (1);
	}
	//ft_putendl("CLOSE OK");
	while(1);
	return (0);
}
