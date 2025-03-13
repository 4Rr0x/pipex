/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:33:49 by jopedro-          #+#    #+#             */
/*   Updated: 2025/03/13 11:38:34 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

# include "../lib/42_libft/libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_pipex
{
	int	fd1;
	int	fd2;
	int	pipe_fds[2];
}	t_pipex;

void	parse(char **av, t_pipex *pp);
void	exit_pgm(char *str, int fd);
t_pipex	*init_struct(void);
void	init_pipe(t_pipex *pp);
void	exec_command(char *av, char **envp);
void	free_split(char **strs);
void	child(char **av, char **envp, t_pipex *pp);
void	parent(char **av, char **envp, t_pipex *pp);

#endif
