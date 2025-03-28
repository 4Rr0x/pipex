/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:33:38 by jopedro-          #+#    #+#             */
/*   Updated: 2025/03/12 17:25:47 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pp;
	int		i;

	if (ac < 5)
		usage();
	pp = init_struct();
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		i = 3;
		here_doc(av, ac, pp);
	}
	else
	{
		i = 2;
		pp->fd1 = open_file(av[1], 0, pp);
		pp->fd2 = open_file(av[ac - 1], 1, pp);
		dup2(pp->fd1, 0);
		close(pp->fd1);
	}
	while (i < ac - 2)
		do_pipe(av[i++], envp, pp);
	dup2(pp->fd2, 1);
	exec_command(av[ac - 2], envp, pp);
	free_struct(pp);
	return (0);
}
