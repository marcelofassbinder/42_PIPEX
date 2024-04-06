/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:18:30 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/06 18:05:47 by mfassbin         ###   ########.fr       */
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

void	first_process(t_pipex_b *ppx, int infile)
{
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
}

//t_pipex_b init_bonus(char **argv, )

int main(int argc, char **argv)
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
			first_process(&ppx, infile);
	/* 	if (ppx.pid > 0)
		{

		}
 */		i++;
	}
	/* ppx = init_struct(argv, envp);
	if (pipe(ppx.fd) == -1)
		free_and_exit(&ppx, "pipe", EXIT_FAILURE);
	ppx.pid = fork();
	if (ppx.pid == 0) // PROCESSO FILHO
		child_process(&ppx, argv[1], envp);
	if (ppx.pid > 0) // PROCESSO PAI
		parent_process(&ppx, argv[4], envp); */
}