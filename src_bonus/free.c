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

#include "../inc/pipex.h"

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

void	free_gnl(char *line)
{
	char	*ln;

	free(line);
	ln = get_next_line(0);
	while (ln)
	{
		free(ln);
		ln = get_next_line(0);
	}
}
