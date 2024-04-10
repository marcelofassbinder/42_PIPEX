/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:25:52 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/10 19:43:51 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/**
 * Initializes the pipex_b structure with the given arguments.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @param envp An array of strings containing the environment variables.
 * @return The initialized pipex_b structure.
 */
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

/**
 * Create, open and close a "here_doc" file which will include all the 
 * characters read from the standard input, through "get_next_line" function.
 * 
 * @param ppx The pipex_b struct containing the necessary information for execution.
 * @param argv The command line arguments.
 * @return The file descriptor of "here_doc" file.
 */
int here_doc(t_pipex_b *ppx, char **argv)
{
    int     fd;
    char    *line;
	char	*limit;

	limit = argv[2];
    fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd < 0)
        free_and_exit_b(ppx, "open", EXIT_FAILURE);
    while(1)
    {
        ft_printf(1, ">");
        line = get_next_line(0);
        if (ft_strncmp(line, limit, ft_strlen(limit)) == 0 && 
            ft_strlen(line) == ft_strlen(limit) + 1)
        {
            free(line);
			get_next_line(-1);
            break;
        }
        write(fd, line, ft_strlen(line));
        free(line);
    }
	close(fd);
    return(fd);
}

/**
 * Defines the command for the "execve" function, if the string contains quotes,
 * they will be deleted and the string will be splitted by "ft_split_trim", 
 * otherwise, "ft_split" will handle the command.
 *
 * @param ppx   A pointer to the `t_pipex_b` struct.
 * @param i     The current number of the iteration in the main function.
 * @param argv  The double pointer to the command arguments.
 * @return      The updated double pointer to the command arguments.
 */
char **define_command(t_pipex_b *ppx, int i, char **argv)
{
	char **command;

	command = NULL;
	if (ppx->here_doc == 1)
	{
		if (ft_strchr(argv[3 + i], 39) != NULL)
			command = ft_split_trim(argv[3 + i], 39);
		else
			command = ft_split(argv[3 + i], ' ');
	}
	if (ppx->here_doc == 0)
	{
		if (ft_strchr(argv[2 + i], 39) != NULL)
            command = ft_split_trim(argv[2 + i], 39);
        else
            command = ft_split(argv[2 + i], ' ');
	}
	return(command);
}

/**
 * Executes a process through "execve" function. Tests all the possible paths,
 * until find the correct one. When this happens the function will incorporate 
 * the whole process and will execute the command with the input and output set
 * for the program.
 *
 * @param ppx The pipex_b struct containing program information.
 * @param i The current number of the iteration in the main function.
 * @param argv The command line arguments.
 * @param envp The environment variables.
 */
void	exec_command(t_pipex_b *ppx, int i, char **argv, char **envp)
{
	int		j;
	char	*temp;
	char 	**command;

	command = define_command(ppx, i, argv);
	j = -1;
	while(ppx->path[++j])
	{
		temp = ppx->path[j];
		ppx->path[j] = ft_strjoin(ppx->path[j], command[0]);
		free(temp);
		execve(ppx->path[j], command, envp);
	}
	free_command(ppx, command, command[0], EXIT_COMMAND);
}
