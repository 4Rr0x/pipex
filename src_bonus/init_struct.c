/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:42:45 by jopedro-          #+#    #+#             */
/*   Updated: 2025/03/24 16:07:57 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

t_pipex	*init_struct(void)
{
	t_pipex	*pp;

	pp = malloc(sizeof(t_pipex));
	pp->fd1 = 0;
	pp->fd2 = 0;
	pp->pipe_fds[0] = -1;
	pp->pipe_fds[1] = -1;
	return (pp);
}

void	init_pipe(t_pipex *pp)
{
	if (pipe(pp->pipe_fds) == -1)
		exit_pgm("Error creating pipe\n", 2, pp);
}
