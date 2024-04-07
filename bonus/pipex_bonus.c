/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:18:30 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/07 13:48:50 by mfassbin         ###   ########.fr       */
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
/* void	exec_process(t_pipex *ppx, char **envp, char c)
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
} */
//definir o comando e executa-lo
void	exec_command(t_pipex_b *ppx, char **argv, int i, char **envp)
{
	int		i;
	char	*command;

	command = define_command(ppx, )
	if (ppx->here_doc == 1)
		command = 
	i = -1;
	while(ppx->path[i++])
	{
		
	}
}

void	first_process(t_pipex_b *ppx, char **argv)
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
	//execute_process()
}

void	mid_process(t_pipex_b *ppx, int i)
{
	if(pipe(ppx->pipes[i]) == -1)
		perror("pipe");
	close(ppx->pipes[i][1]);
	dup2(ppx->pipes[i -1][1], STDIN_FILENO);
	dup2(ppx->pipes[i][0], STDOUT_FILENO);
	close(ppx->pipes[i][0]);
	close(ppx->pipes[i - 1][1]);
	//execute_process()
}

void	last_process(t_pipex_b *ppx, char **argv, int argc, int i)
{
	int outfile;

	outfile = open(argv[argc -1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (outfile < 0)
		perror(argv[argc - 1]);
	if (pipe(ppx->pipes[i] == -1))
		perror("pipe");
	close(ppx->pipes[i][1]);
	dup2(ppx->pipes[i - 1][1], STDIN_FILENO);
	dup2(ppx->pipes[i][0], STDOUT_FILENO);
	close(ppx->pipes[i][0]);
	close(ppx->pipes[i - 1][1]);
	//execute_command
}


t_pipex_b init_struct(int argc, char **argv, char **envp)
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
	ppx.commands = ft_calloc(sizeof(char *), ppx.processes);
	ppx.path = ft_path(envp);
	ppx.pid = 0;
}

int main(int argc, char **argv, char envp)
{
	t_pipex_b   ppx;
    int         infile;
	int			i;

    ppx = (t_pipex_b){0};
	
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
	while(ppx.pipes[i])
	{
		ppx.pid = fork();
		if (ppx.pid == 0)
		{
			if (i == 0)
				first_process(&ppx, infile);
			else
				mid_process(&ppx, i);
		}
		if (ppx.pid > 0)
			return ;
		i++;
	}
	last_process(&ppx, argv, argc, i);
	/* ppx = init_struct(argv, envp);
	if (pipe(ppx.fd) == -1)
		free_and_exit(&ppx, "pipe", EXIT_FAILURE);
	ppx.pid = fork();
	if (ppx.pid == 0) // PROCESSO FILHO
		child_process(&ppx, argv[1], envp);
	if (ppx.pid > 0) // PROCESSO PAI
		parent_process(&ppx, argv[4], envp); */
}