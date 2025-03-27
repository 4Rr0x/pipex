/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:44:37 by jopedro-          #+#    #+#             */
/*   Updated: 2025/03/12 17:46:39 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	free_struct(t_pipex *pp)
{
	if (pp)
	{
		close(pp->pipe_fds[0]);
		close(pp->pipe_fds[1]);
		close(pp->fd1);
		close(pp->fd2);
	}
	free(pp);
}
