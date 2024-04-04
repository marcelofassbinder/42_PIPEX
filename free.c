/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:21:08 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/03 16:23:43 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **cmd)
{
	int i;

	i = -1;
	while(cmd[++i])
		free(cmd[i]);
	free(cmd);
}

void free_and_exit(t_pipex *ppx, char *error)
{
	perror(error);
	free_array(ppx->path);
	free_array(ppx->cmd1);
	free_array(ppx->cmd2);
	exit(EXIT_FAILURE);
}