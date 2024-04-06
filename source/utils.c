/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:23:11 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/06 17:07:34 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_input(int argc, char **argv)
{
	int i;
	
	if (argc != 5)
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

void	exec_process(t_pipex *ppx, char **envp, char c)
{
	int i;

	if(c == 'c')
	{
		i = -1;
		while(ppx->path[++i])
		{
			ppx->path[i] = ft_strjoin(ppx->path[i], ppx->cmd1[0]);
			execve(ppx->path[i], ppx->cmd1, envp); //SE PASSAR DESTA LINHA É PQ NAO EXECUTOU
		}
		free_and_exit(ppx, ppx->cmd1[0], EXIT_COMMAND);
	}
	if (c == 'p')
	{
		i = -1;
		while(ppx->path[++i])
		{
			ppx->path[i] = ft_strjoin(ppx->path[i], ppx->cmd2[0]);
			execve(ppx->path[i], ppx->cmd2, envp); //SE PASSAR DESTA LINHA É PQ NAO EXECUTOU
		}
		free_and_exit(ppx, ppx->cmd2[0], EXIT_COMMAND);
	}
}

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
