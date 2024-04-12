/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:15:11 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/12 11:09:48 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/**
 * Opens the input file for pipex.
 * 
 * @param ppx The pipex_b struct containing the necessary information.
 * @param argv The command line arguments.
 * @return Returns the infile fd opened.
 */
int	open_infile(t_pipex_b *ppx, char **argv)
{
	int	infile;

	if (ppx->here_doc == 0)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile < 0)
			free_and_exit_b(ppx, argv[1], EXIT_FAILURE);
	}
	if (ppx->here_doc == 1)
	{
		here_doc(ppx, argv);
		infile = open("here_doc", O_RDONLY, 0666);
		if (infile == -1)
			free_and_exit_b(ppx, "here_doc", EXIT_FAILURE);
	}
	return (infile);
}

/**
 * Executes the child process for pipex_bonus.
 *
 * @param ppx The pipex_b struct containing necessary information.
 * @param fd_redir The file descriptor for input redirection.
 * @param i The current number of the iteration in the main function.
 * @param argv The command line arguments.
 * @param envp The environment variables.
 */
void	child_process_b(t_pipex_b *ppx, int *fd_redir, int i, char **argv)
{
	dup2(*fd_redir, STDIN_FILENO);
	close(*fd_redir);
	close(ppx->fd[0]);
	dup2(ppx->fd[1], STDOUT_FILENO);
	close(ppx->fd[1]);
	exec_command(ppx, i, argv);
}

/**
 * Parent process for pipex_bonus. This function makes fd_redir receive the read
 * end of the pipe, 
 * turning it into the input of the next process.
 *
 * @param ppx       The pipex_b struct containing the necessary information.
 * @param fd_redir  The file descriptor for input/output redirection.
 */
void	parent_process_b(t_pipex_b *ppx, int *fd_redir)
{
	close(*fd_redir);
	close(ppx->fd[1]);
	*fd_redir = ppx->fd[0];
}

/**
 * Executes the last process in the pipex program, waiting untill all the 
 * children processes end, to execute the last command. 
 *
 * @param ppx The pipex_b struct containing program information.
 * @param i The current number of the iteration in the main function.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @param envp The environment variables.
 */
void	last_process(t_pipex_b *ppx, int i, int argc, char **argv)
{
	int	outfile;
	int	j;
	int	exit_code;

	j = 0;
	while (j < ppx->processes - 1)
	{
		waitpid(0, &exit_code, 0);
		j++;
	}
	outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (outfile == -1)
		free_and_exit_b(ppx, argv[argc -1], EXIT_FAILURE);
	dup2(outfile, STDOUT_FILENO);
	close(ppx->fd[1]);
	close(outfile);
	if (ppx->here_doc == 1)
		unlink("here_doc");
	exec_command(ppx, i, argv);
}
