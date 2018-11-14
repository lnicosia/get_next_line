/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:28:08 by lnicosia          #+#    #+#             */
/*   Updated: 2018/11/14 14:46:03 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

int		get_next_line(const int fd, char **line);

int		main(int argc, char **argv)
{
	int	fd = 0;
	char	**line;

	if (argc == 1)
	{
		ft_putendl("Err NO FILE");
		return (1);
	}
	line = (char**)malloc(sizeof(char*));
	if (!(fd = open(argv[1], O_RDONLY)))
	{
		ft_putendl("Err OPEN");
		return (1);
	}
	while (get_next_line(fd, line) == 1)
		ft_putendl(*line);
	if (close(fd) == -1)
	{
		ft_putendl("Err CLOSE");
		return (1);
	}
	return (0);
}
