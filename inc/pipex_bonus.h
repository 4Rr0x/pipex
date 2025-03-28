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

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../lib/42_libft/libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int	fd1;
	int	fd2;
	int	pipe_fds[2];
}	t_pipex;

void	exit_pgm(char *str, int fd, t_pipex *pp);
t_pipex	*init_struct(void);
void	init_pipe(t_pipex *pp);
void	exec_command(char *av, char **envp, t_pipex *pp);
void	free_struct(t_pipex *pp);
void	execute_pipeline(t_pipex *pp, char **envp, char **av, int ac);
int		open_file(char *av, int flag, t_pipex *pp);
void	here_doc(char **av, int ac, t_pipex *pp);
void	do_pipe(char *cmd, char **envp, t_pipex *pp);
void	usage(void);

#endif
