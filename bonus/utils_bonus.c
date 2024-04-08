/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:25:52 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/08 16:57:02 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_pipex_b init_bonus(int argc, char **argv, char **envp)
{
	t_pipex_b	ppx;

	ppx.here_doc = 0;
	if (ft_strcmp(argv[1], "here_doc") == 0)
		ppx.here_doc = 1;
	ppx.processes = argc - 3 - ppx.here_doc;
	ppx.fd[0] = 0;
	ppx.fd[1] = 0;
	ppx.path = ft_path(envp);
	ppx.pid = 0;
	return(ppx);
}

void	handle_input_b(int argc, char **argv)
{
	int i;
	
	if (argc < 5)
	{
		ft_printf(2, "Error\nCorrect usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while(argv[++i])
	{
		if(argv[i][0] == 0)
		{
			ft_printf(2, "Error\nInvalid arguments\n");
			exit(EXIT_FAILURE);
		}
	}
}