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
