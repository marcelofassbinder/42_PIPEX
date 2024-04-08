/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:15:11 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/08 17:25:26 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int here_doc(char **argv)
{
    int     fd;
    char    *line;
	char	*limit;

	limit = argv[2];
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
        if (ft_strncmp(line, limit, ft_strlen(limit)) == 0 && 
            ft_strlen(line) == ft_strlen(limit) + 1)
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
	while(ppx->path[++j])
	{
		ppx->path[j] = ft_strjoin(ppx->path[j], command[0]);
		execve(ppx->path[j], command, envp);
	}
	perror("execve");
}

int open_infile(t_pipex_b *ppx, char **argv)
{
	int infile;

	if (ppx->here_doc == 0)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile < 0)
			perror("open infile");
	}
	if (ppx->here_doc == 1)
		infile = here_doc(argv);
	return (infile);
}

void	last_process(t_pipex_b *ppx, int i, int argc, char **argv, char **envp)
{
	int	outfile;

	outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (outfile == -1)
		perror("open outfile");
	dup2(outfile, STDOUT_FILENO);
	close(ppx->fd[1]);
	close(outfile);
	exec_command(ppx, i, argv, envp);
	perror("execve");
}

void	child_process_b(t_pipex_b *ppx, int fd_redir, int i, char **argv, char **envp)
{
	dup2(fd_redir, STDIN_FILENO); //transforma o fd do infile ou do pipe anterior no input deste processo
	close(fd_redir);//fecha o fd do infile ou do pipe anterior
	dup2(ppx->fd[1], STDOUT_FILENO);//transforma o fd de escrita do pipe no output do processo
	close(ppx->fd[0]);// fecha o fd de leitura
	close(ppx->fd[1]);// fecha o fd de escrita
	if (ppx->here_doc == 1)
		unlink("here_doc");//deleta o arquivo "here_doc"
	exec_command(ppx, i, argv, envp);//executa o comando
}

void	parent_process_b(t_pipex_b *ppx, int fd_redir)
{
	//wait(NULL);
	close(fd_redir);
	close(ppx->fd[1]);
	fd_redir = ppx->fd[0];
}

int main(int argc, char **argv, char **envp)
{
	t_pipex_b   ppx;
	int			fd_redir;
	int			i;

	handle_input_b(argc, argv);
    ppx = init_bonus(argc, argv, envp);
	fd_redir = open_infile(&ppx, argv);
	i = 0;
	while(i < ppx.processes - 1)
	{
		if (pipe(ppx.fd) == -1)
			perror("pipe");
		ppx.pid = fork();
		if (ppx.pid == -1)
			perror("fork");
		if (ppx.pid == 0)
			child_process_b(&ppx, fd_redir, i, argv, envp);
		if (ppx.pid > 0)
			parent_process_b(&ppx, fd_redir);
		i++;
	}
	dup2(fd_redir, STDIN_FILENO);
	close(fd_redir);
	last_process(&ppx, i, argc, argv, envp);
}

