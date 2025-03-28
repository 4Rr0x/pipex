/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:03:06 by jopedro-          #+#    #+#             */
/*   Updated: 2025/03/13 11:38:57 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	handle_all(char **av, char **envp, t_pipex *pp)
{
	pid_t	pid;
	pid_t	pid2;

	pid = fork();
	if (pid == -1)
		exit_pgm("Error creating pid\n", 2, pp);
	if (pid == 0)
		child(av, envp, pp);
	pid2 = fork();
	if (pid2 == -1)
		exit_pgm("Error creating pid2\n", 2, pp);
	if (pid2 == 0)
		parent(av, envp, pp);
	close(pp->fd1);
	close(pp->fd2);
	close(pp->pipe_fds[0]);
	close(pp->pipe_fds[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_struct(pp);
}

char	*find_path(char **envp, char *cmd)
{
	int		i;
	char	*path;
	char	**parr;
	char	*partial;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	parr = ft_split(envp[i] + 5, ':');
	i = 0;
	while (parr[i])
	{
		partial = ft_strjoin(parr[i], "/");
		path = ft_strjoin(partial, cmd);
		free(partial);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (parr[++i])
		free (parr[i]);
	free(parr);
	return (0);
}

void	exec_command(char *av, char **envp, t_pipex *pp)
{
	int		i;
	char	**cmd;
	char	*path;

	i = 0;
	cmd = ft_split(av, ' ');
	if (!cmd[0])
	{
		free(cmd);
		exit_pgm("Command not found\n", 2, pp);
	}
	path = find_path(envp, cmd[0]);
	if (!path)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		exit_pgm("Error finding path\n", 2, pp);
	}
	if (execve(path, cmd, envp) == -1)
		exit_pgm("Error executing command\n", 2, pp);
}

void	child(char **av, char **envp, t_pipex *pp)
{
	dup2(pp->pipe_fds[1], STDOUT_FILENO);
	dup2(pp->fd1, STDIN_FILENO);
	close(pp->pipe_fds[0]);
	close(pp->pipe_fds[1]);
	exec_command(av[2], envp, pp);
}

void	parent(char **av, char **envp, t_pipex *pp)
{
	dup2(pp->pipe_fds[0], STDIN_FILENO);
	dup2(pp->fd2, STDOUT_FILENO);
	close(pp->pipe_fds[1]);
	close(pp->pipe_fds[0]);
	exec_command(av[3], envp, pp);
}
