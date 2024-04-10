/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:30:58 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/10 19:43:51 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/**
 * The main function of the pipex_bonus program.
 * 
 * Crete a loop where it will iterate "processes - 1" times, creating pipes and
 * forking to clone the processes. Outside the loop the function clones the 
 * "fd_redir"(that will be the read end of the last pipe) as the input of the 
 * process, and executes the last process, transforming the outfile in the 
 * standard output.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @param envp An array of strings containing the environment variables.
 * @return An integer value representing the exit status of the program.
 */
int main(int argc, char **argv, char **envp)
{
	t_pipex_b   ppx;
	int			fd_redir;
	int			i;

	handle_input(argc, argv);
    ppx = init_bonus(argc, argv, envp);
	fd_redir = open_infile(&ppx, argv);
	i = 0;
	while(i < ppx.processes - 1)
	{
		if (pipe(ppx.fd) == -1)
			free_and_exit_b(&ppx, "pipe", EXIT_FAILURE);
		ppx.pid = fork();
		if (ppx.pid == -1)
			free_and_exit_b(&ppx, "fork", EXIT_FAILURE);
		if (ppx.pid == 0)
			child_process_b(&ppx, &fd_redir, i, argv, envp);
		if (ppx.pid > 0)
			parent_process_b(&ppx, &fd_redir);
		i++;
	}
	dup2(fd_redir, STDIN_FILENO);
	close(fd_redir);
	last_process(&ppx, i, argc, argv, envp);
}