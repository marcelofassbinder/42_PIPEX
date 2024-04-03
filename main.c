/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcelo <marcelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:25:38 by marcelo           #+#    #+#             */
/*   Updated: 2024/04/02 21:16:04 by marcelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exchange_fd(t_pipex *ppx, int file, char process)
{
	if (process == 'c')
	{
		close(ppx->end[0]); // FECHA O end DE LEITURA DO PIPE
		dup2(file, STDIN_FILENO);//TRANSFORMA O FILE1 NO INPUT DO PROCESSO
		dup2(ppx->end[1], STDOUT_FILENO); // TRANSFORMA O end[1] DO PIPE EM OUTPUT DO PROCESSO
		close(file);
	}
	if (process == 'p')
	{
		close(ppx->end[1]); // FECHA O end DE ESCRITA DO PIPE
		dup2(file, STDOUT_FILENO); // TRANSFORMA O FILE2 NO OUTPUT DO PROCESSO
		dup2(ppx->end[0], STDIN_FILENO);// TRANSFORMA O FD[0] NO INPUT DO PROCESSO
		close (file);
	}
}

char **ft_path(char **envp)
{
	char **path;
	int i;

	i = 0;
	while(ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	envp[i] = ft_strtrim(envp[i], "PATH=");
	path = ft_split(envp[i], ':');
	i = -1;
	while(path[++i])
		path[i] = ft_strjoin(path[i], "/");
	return(path);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex ppx;
	int file1;
	int file2;
	char **cmd1;
	char **cmd2;
	char **path;
	int i;

	(void) argc;
	ppx = (t_pipex){0};
	path = ft_path(envp);
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	if (pipe(ppx.end) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	ppx.pid = fork();
	if (ppx.pid == 0) // PROCESSO FILHO
	{
		file1 = open(argv[1], O_RDONLY);
		if (file1 < 0)
		{
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}
		exchange_fd(&ppx, file1, 'c');
		i = -1;
		while(path[++i])
		{
			execve(ft_strjoin(path[i], cmd1[0]), cmd1, envp); //SE PASSAR DESTA LINHA É PQ NAO EXECUTOU
			free(path[i]);
		}
		perror(cmd1[0]);
		exit(EXIT_FAILURE);
	}
	if (ppx.pid > 0) // PROCESSO PAI
	{
		wait(NULL); // ESPERA ATE O PROCESSO FILHO ACABAR
		file2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		exchange_fd(&ppx, file2, 'p');
		i = -1;
		while(path[++i])
			execve(ft_strjoin(path[i], cmd2[0]), cmd2, envp); //SE PASSAR DESTA LINHA É PQ NAO EXECUTOU
		perror("Error");
		exit(EXIT_FAILURE);
	}

}
