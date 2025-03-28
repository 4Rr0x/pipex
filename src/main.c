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

#include "../inc/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pp;

	if (ac != 5)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		return (1);
	}
	pp = init_struct();
	parse(av, pp);
	init_pipe(pp);
	handle_all(av, envp, pp);
	return (0);
}
