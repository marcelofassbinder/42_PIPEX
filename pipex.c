/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:25:38 by marcelo           #+#    #+#             */
/*   Updated: 2024/04/03 19:56:54 by mfassbin         ###   ########.fr       */
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

t_pipex init_struct(char **argv, char **envp)
{
	t_pipex	ppx;

	ppx.pid = 0;
	ppx.fd[0] = 0;
	ppx.fd[1] = 0;
	ppx.path = ft_path(envp);
	ppx.cmd1 = ft_split(argv[2], ' ');
	ppx.cmd2 = ft_split(argv[3], ' ');
	return (ppx);
}

char **tira_aspas(char *cmd)
{
	char 	*first;
	char 	**cmd_split;
	char 	*cmd_args;
	int		i;

	cmd_split = ft_split(cmd, ' ');
	first = cmd_split[0];
	i = 0;
	while(cmd_split[i])
	{
		if(ft_strchr(cmd_split[i], 39))
		{
			cmd_split[i] = ft_strtrim(cmd_split[i], "'");
			ft_printf(1, "new: %s\n", cmd_split[i]);
		}	
		i++;
	}
	i = 1;
	while (cmd_split[i])
	{
		cmd_args = ft_strjoin_space(cmd_split[i], cmd_split[i + 1]);
		i++;
	}
	cmd_split[1] = cmd_args;
	cmd_split[2] = NULL;
	ft_printf(1, "cmd_split[0]: %s\n", cmd_split[0]);
	return (cmd_split);
}

void	handle_args(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_printf(2, "Error\nCorrect usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (ft_strchr(argv[2], 39) != NULL) // SE TIVER ASPAS SIMPLES
		 = tira_aspas(argv[2]);
	if (ft_strchr(argv[3], 39) != NULL) // SE TIVER ASPAS SIMPLES
		argv[3] = tira_aspas(argv[3]);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex ppx;
	int file;
	
	handle_args(argc, argv);
	ppx = init_struct(argv, envp);
	if (pipe(ppx.fd) == -1)
		free_and_exit(&ppx, "pipe");
	ppx.pid = fork();
	if (ppx.pid == 0) // PROCESSO FILHO
	{
		file = open(argv[1], O_RDONLY);
		if (file < 0)
			free_and_exit(&ppx, argv[1]);
		exchange_fd(&ppx, file, 'c');
		exec_process(&ppx, envp, 'c');
	}
	if (ppx.pid > 0) // PROCESSO PAI
	{
		wait(NULL); // ESPERA ATE O PROCESSO FILHO ACABAR
		file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (file < 0)
			free_and_exit(&ppx, argv[4]);
		exchange_fd(&ppx, file, 'p');
		exec_process(&ppx, envp, 'p');
	}
}
