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

#include "../inc/pipex_bonus.h"

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

void	do_pipe(char *cmd, char **envp, t_pipex *pp)
{
	pid_t	pid;

	if (pipe(pp->pipe_fds) == -1)
		exit_pgm("Error creating pipe\n", 2, pp);
	pid = fork();
	if (pid == -1)
		exit_pgm("Error creating fork\n", 2, pp);
	if (pid == 0)
	{
		close(pp->pipe_fds[0]);
		dup2(pp->pipe_fds[1], 1);
		close(pp->pipe_fds[1]);
		exec_command(cmd, envp, pp);
	}
	else
	{
		close(pp->pipe_fds[1]);
		dup2(pp->pipe_fds[0], 0);
		close(pp->pipe_fds[0]);
	}
}

void	here_doc_in(char **av, t_pipex *pp)
{
	char	*ret;

	close(pp->pipe_fds[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (!ret)
		{
			exit_pgm("Error reading input\n", 2, pp);
		}
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
		{
			free(ret);
			break ;
		}
		ft_putstr_fd(ret, pp->pipe_fds[1]);
		free(ret);
	}
	close(pp->pipe_fds[1]);
}

void	here_doc(char **av, int ac, t_pipex *pp)
{
	pid_t	pid;

	pp->fd2 = open_file(av[ac - 1], 2, pp);
	if (ac < 6)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return ;
	}
	if (pipe(pp->pipe_fds) == -1)
		exit_pgm("Error creating pipe\n", 2, pp);
	pid = fork();
	if (pid == -1)
		exit_pgm("Error creating pid\n", 2, pp);
	if (!pid)
		here_doc_in(av, pp);
	else
	{
		close(pp->pipe_fds[1]);
		dup2(pp->pipe_fds[0], 0);
		wait(NULL);
	}
}
