/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:35:23 by jopedro-          #+#    #+#             */
/*   Updated: 2025/03/11 17:37:34 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	exit_pgm(char *str, int fd, t_pipex *pp)
{
	free_struct(pp);
	ft_putstr_fd(str, fd);
	if (fd == 2)
		exit(0);
	else
		exit (1);
}

void	usage(void)
{
	ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> \
		<file>\n", 1);
	exit(1);
}
