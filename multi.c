/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:10:16 by gaerhard          #+#    #+#             */
/*   Updated: 2018/11/20 14:27:13 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "fcntl.h"

int		main(int argc, char **argv)
{
	int		*fd;
	int		i;
	char	*line;

	i = 1;
	fd = malloc(sizeof(int) * argc);
	if (argc < 2)
	{
		ft_putstr("File name missing.\n");
		return (0);
	}
	while (i < argc)
	{
		fd[i] = open(argv[i], O_RDONLY);
		i++;
	}
	i = 1;
	while (get_next_line(fd[i], &line) > 0)
	{
		ft_putstr("boucle: ");
		ft_putendl(line);
		free(line);
		line = NULL;
		i++;
		if (i >= argc)
			i = 1;
	}
	ft_putstr("gnl = 0: ");
	ft_putendl(line);
	i = 1;
	while (i < argc)
	{
		close(fd[i]);
		i++;
	}
	free(fd);
	while (1);
	ft_putendl("boucle infinie pour check les leaks");
}
