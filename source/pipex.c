/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:25:38 by marcelo           #+#    #+#             */
/*   Updated: 2024/04/08 11:51:59 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipex *ppx, char *file, char **envp)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		free_and_exit(ppx, file, EXIT_FAILURE);
	exchange_fd(ppx, fd, 'c');
	exec_process(ppx, envp, 'c');
}

void	parent_process(t_pipex *ppx, char *file, char **envp)
{
	int fd;

	wait(NULL); // ESPERA ATE O PROCESSO FILHO ACABAR
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
		free_and_exit(ppx, file, EXIT_FAILURE);
	exchange_fd(ppx, fd, 'p');
	exec_process(ppx, envp, 'p');
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

int main(int argc, char **argv, char **envp)
{
	t_pipex ppx;

	handle_input(argc, argv);
	ppx = init_struct(argv, envp);
	if (pipe(ppx.fd) == -1)
		free_and_exit(&ppx, "pipe", EXIT_FAILURE);
	ppx.pid = fork();
	if (ppx.pid == 0) // PROCESSO FILHO
		child_process(&ppx, argv[1], envp);
	if (ppx.pid > 0) // PROCESSO PAI
		parent_process(&ppx, argv[4], envp);
}
