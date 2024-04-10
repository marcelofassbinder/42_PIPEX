/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:23:11 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/10 19:43:12 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * @brief Exchanges the file descriptor for a given process in the pipex structure.
 *
 * This function is responsible for exchanging the file descriptor for a 
 * specific process in the pipex structure. For the child process, it clones 
 * the infile fd as the standard input for the process and transforms the fd[1]
 * from the pipe to the standard output. For the parent process, it clones the 
 * outfile fd as the standard output and transforms the fd[0] from the pipe to 
 * the standard input of the process.
 *
 * @param ppx The pointer to the pipex structure.
 * @param file The file descriptor to be exchanged.
 * @param process The process identifier.'c' for child or 'p' for parent.
 */
void	exchange_fd(t_pipex *ppx, int file, char process)
{
	if (process == 'c')
	{
		close(ppx->fd[0]); // FECHA O end DE LEITURA DO PIPE
		dup2(file, STDIN_FILENO);//TRANSFORMA O FILE1 NO INPUT DO PROCESSO
		dup2(ppx->fd[1], STDOUT_FILENO); // TRANSFORMA O end[1] DO PIPE EM OUTPUT DO PROCESSO
		close(ppx->fd[1]); // FECHA O end DE ESCRITA DO PIPE
		close(file);

	}
	if (process == 'p')
	{
		close(ppx->fd[1]); // FECHA O end DE ESCRITA DO PIPE
		dup2(file, STDOUT_FILENO); // TRANSFORMA O FILE2 NO OUTPUT DO PROCESSO
		dup2(ppx->fd[0], STDIN_FILENO);// TRANSFORMA O FD[0] NO INPUT DO PROCESSO
		close(ppx->fd[0]); // FECHA O end DE LEITURA DO PIPE
		close(file);
	}
}

/**
 * Executes the execve system call for a specific command.
 * 
 * @param ppx   The pipex structure.
 * @param i     The index of path array.
 * @param cmd   The command to execute.
 * @param envp  The environment variables.
 */
void	execve_call(t_pipex *ppx, int i, char **cmd, char **envp)
{
	char *temp;

	temp = ppx->path[i];
	ppx->path[i] = ft_strjoin(ppx->path[i], cmd[0]);
	execve(ppx->path[i], cmd, envp);
	free(temp);
}

/**
 * Executes a process through "execve" function. Tests all the possible paths,
 * until find the correct one. When this happens the function will incorporate 
 * the whole process and will execute the command with the input and output set
 * for the program.
 *
 * @param ppx   A pointer to the pipex structure.
 * @param envp  The environment variables.
 * @param c     The character representing the command to execute.
 */
void	exec_process(t_pipex *ppx, char **envp, char c)
{
	int 	i;

	if(c == 'c')
	{
		i = -1;
		while(ppx->path[++i])
			execve_call(ppx, i, ppx->cmd1, envp);
		free_and_exit(ppx, ppx->cmd1[0], EXIT_COMMAND);
	}
	if (c == 'p')
	{
		i = -1;
		while(ppx->path[++i])
			execve_call(ppx, i, ppx->cmd2, envp);
		free_and_exit(ppx, ppx->cmd2[0], EXIT_COMMAND);
	}
}

/**
 * Retrieves the PATH environment variable and returns it as an array of strings,
 * adding a '/' in the end of each string, turning it valid to be used by "execve". 
 * 
 * @param envp The array of environment variables.
 * @return An array of strings containing the directories specified in the PATH variable.
 */
char **ft_path(char **envp)
{
	char **path;
	char *temp;
	int i;

	i = 0;
	while(ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	temp = ft_strtrim(envp[i], "PATH=");
	path = ft_split(temp, ':');
	i = -1;
	while(path[++i])
		path[i] = ft_strjoin2(path[i], "/");
	free(temp);
	return(path);
}

/**
 * Splits a string into an array of strings, removing leading and trailing 
 * whitespace from each element.
 *
 * @param str The string to be split and trimmed.
 * @param c The delimiter character used to split the string.
 * @return An array of strings, where each element is a trimmed substring of 
 * the original string.
 */
char **ft_split_trim(char *str, char c)
{
    char    *first_trim;
    char    **split;
    char    **trim;
    int     i;

    first_trim = ft_strtrim(str, " ");
    split = ft_split(first_trim, c);
    free(first_trim);
    trim = ft_calloc(sizeof(char *), 3);
    i = -1;
    while (split[++i])
    {
        trim[i] = ft_strtrim(split[i], " ");
    }
    free_array(split);
    return(trim);
}
