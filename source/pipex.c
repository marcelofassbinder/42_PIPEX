/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:25:38 by marcelo           #+#    #+#             */
/*   Updated: 2024/04/10 19:52:16 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * Handles the input arguments, exiting the program and printing an error 
 * message in case of error.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 */
void	handle_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5)
		error_exit ("Error\nCorrect usage: %s file1 cmd1 cmd2 file2\n", \
		EXIT_FAILURE);
	i = -1;
	while (argv[++i])
	{
		if (argv[i][0] == 0 || argv[i][0] == 39)
			error_exit("Error\nInvalid arguments\n", EXIT_FAILURE);
		j = 0;
		while (!ft_isspace(argv[i][j]))
		{
			if (!argv[i][++j])
				error_exit("Error\nEmpty string\n", EXIT_FAILURE);
		}
	}
}

/**
 * Executes the child process.
 * 
 * @param ppx The pipex structure.
 * @param file The file to be opened.
 * @param envp The environment variables.
 */
void	child_process(t_pipex *ppx, char *infile, char **envp)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		free_and_exit(ppx, infile, EXIT_FAILURE);
	exchange_fd(ppx, fd, 'c');
	exec_process(ppx, envp, 'c');
}

/**
 * Executes the parent process, waiting for the child process to end.
 * 
 * @param ppx The pipex structure.
 * @param file The file to be opened.
 * @param envp The environment variables.
 */
void	parent_process(t_pipex *ppx, char *outfile, char **envp)
{
	int	fd;

	wait(NULL);
	fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
		free_and_exit(ppx, outfile, EXIT_FAILURE);
	exchange_fd(ppx, fd, 'p');
	exec_process(ppx, envp, 'p');
}

/**
 * Initializes the pipex structure.
 * 
 * @param argv The command-line arguments.
 * @param envp The environment variables.
 * @return The initialized pipex structure.
 */
t_pipex	init_struct(char **argv, char **envp)
{
	t_pipex	ppx;

	ppx.pid = 0;
	ppx.fd[0] = 0;
	ppx.fd[1] = 0;
	ppx.path = ft_path(envp);
	if (ft_strchr(argv[2], 39) != NULL)
		ppx.cmd1 = ft_split_trim(argv[2], 39);
	else
		ppx.cmd1 = ft_split(argv[2], ' ');
	if (ft_strchr(argv[3], 39) != NULL)
		ppx.cmd2 = ft_split_trim(argv[3], 39);
	else
		ppx.cmd2 = ft_split(argv[3], ' ');
	return (ppx);
}
