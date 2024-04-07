/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:34:24 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/07 18:35:21 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
	t_pipex_b   ppx;
    int         infile;
	int			i;

    ppx = init_bonus(argc, argv, envp);
	
	if (ft_strcmp(argv[1], "here_doc") == 0)
    {
		ppx.pipes = ft_calloc(sizeof(int *), argc - 4);
        ppx.here_doc = 1;
        infile = here_doc(argv);
    }
    else
	{
        infile = open(argv[1],  O_WRONLY, 0666);
		ppx.pipes = ft_calloc(sizeof(int *), argc - 3);
	}
	if (infile < 0)
		perror("infile");
	i = 0;
	while(i < ppx.processes)
	{
		ppx.pid = fork();
		if (ppx.pid == 0)
		{
			if (i == 0)
				first_process(&ppx, argv, i, envp);
			else
				mid_process(&ppx, i, argv, envp);
		}
		if (ppx.pid > 0)
			return (0);
		i++;
	}
	last_process(&ppx, argv, argc, i, envp);
	/* ppx = init_struct(argv, envp);
	if (pipe(ppx.fd) == -1)
		free_and_exit(&ppx, "pipe", EXIT_FAILURE);
	ppx.pid = fork();
	if (ppx.pid == 0) // PROCESSO FILHO
		child_process(&ppx, argv[1], envp);
	if (ppx.pid > 0) // PROCESSO PAI
		parent_process(&ppx, argv[4], envp); */
}