/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:18:30 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/08 12:32:21 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int here_doc(char **argv)
{
    int     fd;
    char    *line;

    fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd < 0)
    {
        perror("here_doc");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        ft_printf(1, ">");
        line = get_next_line(0);
        if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0 && 
            ft_strlen(line) == ft_strlen(argv[2]) + 1)
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        free(line);
    }
    return(fd);
}

void	exec_command(t_pipex_b *ppx, int i, char **argv, char **envp)
{
	int		j;
	char 	**command;

	if (ppx->here_doc == 1)
	{
		if (ft_strchr(argv[3 + i], 39) != NULL)
			command = ft_split_trim(argv[3 + i], 39);
		else
			command = ft_split(argv[3 + i], ' ');
	}
	else if (ppx->here_doc == 0)
	{
		if (ft_strchr(argv[2 + i], 39) != NULL)
            command = ft_split_trim(argv[2 + i], 39);
        else
            command = ft_split(argv[2 + i], ' ');
	}
	j = -1;
	while(ppx->path[j++])
	{
		ppx->path[j] = ft_strjoin(ppx->path[j], command[i]);
		execve(ppx->path[j], &command[i], envp);
	}
	perror("execve");
}

void	first_process(t_pipex_b *ppx, char **argv, int i, char **envp)
{
	int infile;

	if (ppx->here_doc == 1)
		infile = here_doc(argv);
	else
		infile = open(argv[1],  O_WRONLY, 0666);
	if (infile < 0)
		perror(argv[1]);
	if (pipe(ppx->pipes[0]) == -1)
		perror("pipe");
	close(ppx->pipes[0][0]);
	dup2(infile, STDIN_FILENO);
	dup2(ppx->pipes[0][1], STDOUT_FILENO);
	close(ppx->pipes[0][1]);
	close(infile);
	if (ppx->here_doc == 1)
	{
    	if (unlink("here_doc") < 0)
    	{
        	perror("unlink");
        	exit(EXIT_FAILURE);
    	}
	}
	exec_command(ppx, i, argv, envp);
}

void	mid_process(t_pipex_b *ppx, int i, char **argv, char **envp)
{
	if(pipe(ppx->pipes[i]) == -1)
		perror("pipe");
	close(ppx->pipes[i][1]);
	dup2(ppx->pipes[i -1][1], STDIN_FILENO);
	dup2(ppx->pipes[i][0], STDOUT_FILENO);
	close(ppx->pipes[i][0]);
	close(ppx->pipes[i - 1][1]);
	exec_command(ppx, i, argv, envp);
}

void	last_process(t_pipex_b *ppx, char **argv, int argc, int i, char **envp)
{
	int outfile;

	outfile = open(argv[argc -1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (outfile < 0)
		perror(argv[argc - 1]);
	if (pipe(ppx->pipes[i]) == -1)
		perror("pipe");
	close(ppx->pipes[i][1]);
	dup2(ppx->pipes[i - 1][1], STDIN_FILENO);
	dup2(ppx->pipes[i][0], STDOUT_FILENO);
	close(ppx->pipes[i][0]);
	close(ppx->pipes[i - 1][1]);
	exec_command(ppx, i, argv, envp);
}

t_pipex_b init_bonus(int argc, char **argv, char **envp)
{
	t_pipex_b	ppx;

	ppx.here_doc = 0;
	ppx.processes = argc - 3;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		ppx.here_doc = 1;
		ppx.processes = argc - 4;
	}
	ppx.pipes = ft_calloc(sizeof(int *), ppx.processes - 1);
	ppx.path = ft_path(envp);
	ppx.pid = 0;
	return(ppx);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex_b   ppx;
	int			i;

    ppx = init_bonus(argc, argv, envp);
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
