/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:32:14 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/10 19:43:03 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * The main function of the program.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @param envp The environment variables.
 * @return The exit status of the program.
 */
int main(int argc, char **argv, char **envp)
{
	t_pipex ppx;

	handle_input(argc, argv);
	ppx = init_struct(argv, envp);
	if (pipe(ppx.fd) == -1)
		free_and_exit(&ppx, "pipe", EXIT_FAILURE);
	ppx.pid = fork();
	if (ppx.pid == -1)
		free_and_exit(&ppx, "fork", EXIT_FAILURE);
	if (ppx.pid == 0) 
		child_process(&ppx, argv[1], envp);
	if (ppx.pid > 0) 
		parent_process(&ppx, argv[4], envp);
}