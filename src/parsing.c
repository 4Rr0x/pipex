/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:31:24 by jopedro-          #+#    #+#             */
/*   Updated: 2025/03/13 11:26:20 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include <fcntl.h>

void	open_files(char *file1, char *file2, t_pipex *pp)
{
	pp->fd1 = open(file1, O_RDONLY);
	if (pp->fd1 == -1)
		exit_pgm("Error opening file1\n", 2);
	pp->fd2 = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pp->fd2 == -1)
		exit_pgm("Error opening file2\n", 2);
}

void	parse(char **av, t_pipex *pp)
{
	open_files(av[1], av[4], pp);
}
