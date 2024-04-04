/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:23:11 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/04 15:35:18 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		free_and_exit(ppx, ppx->cmd1[0]);
	}
	if (c == 'p')
	{
		i = -1;
		while(ppx->path[++i])
		{
			ppx->path[i] = ft_strjoin(ppx->path[i], ppx->cmd2[0]);
			execve(ppx->path[i], ppx->cmd2, envp); //SE PASSAR DESTA LINHA É PQ NAO EXECUTOU
		}
		free_and_exit(ppx, ppx->cmd2[0]);
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
		path[i] = ft_strjoin(path[i], "/");
	free(temp);
	return(path);
}

t_pipex init_struct(char **argv, char **envp)
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
