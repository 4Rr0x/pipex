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

#include "../inc/pipex_bonus.h"

int	open_file(char *file, int flag, t_pipex *pp)
{
	int	fd;

	fd = -1;
	if (flag == 0)
		fd = open(file, O_RDONLY, 0777);
	else if (flag == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		exit_pgm("Error opening file\n", 2, pp);
	return (fd);
}
