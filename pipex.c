/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:25:38 by marcelo           #+#    #+#             */
/*   Updated: 2024/04/04 15:35:18 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipex *ppx, char *file, char **envp)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		free_and_exit(ppx, file);
	exchange_fd(ppx, fd, 'c');
	exec_process(ppx, envp, 'c');
}

void	parent_process(t_pipex *ppx, char *file, char **envp)
{
	int fd;

	wait(NULL); // ESPERA ATE O PROCESSO FILHO ACABAR
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
		free_and_exit(ppx, file);
	exchange_fd(ppx, fd, 'p');
	exec_process(ppx, envp, 'p');
}

int main(int argc, char **argv, char **envp)
{
	t_pipex ppx;

	if (argc != 5)
	{
		ft_printf(2, "Error\nCorrect usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	ppx = init_struct(argv, envp);
	if (pipe(ppx.fd) == -1)
		free_and_exit(&ppx, "pipe");
	ppx.pid = fork();
	if (ppx.pid == 0) // PROCESSO FILHO
		child_process(&ppx, argv[1], envp);
	if (ppx.pid > 0) // PROCESSO PAI
		parent_process(&ppx, argv[4], envp);
}
