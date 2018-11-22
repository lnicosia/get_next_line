/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:10:16 by gaerhard          #+#    #+#             */
/*   Updated: 2018/11/22 10:46:56 by lnicosia         ###   ########.fr       */
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
	int		ret;

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
		ft_putstr(argv[i]); ft_putstr("/fd = "); ft_putnbr(fd[i]); ft_putendl("");
		i++;
	}
	i = 1;
	while ((ret = get_next_line(fd[i], &line)) > 0)
	{
		//ft_putstr("boucle: ");
		ft_putendl(line);
		ft_strdel(&line);
		i++;
		if (i >= argc)
			i = 1;
	}
	ft_putstr("gnl = 0: ");
	ft_strdel(&line);
	i = 1;
	while (i < argc)
	{
		close(fd[i]);
		i++;
	}
	free(fd);
	fd = NULL;
	while (1);
	return (ret);
}
