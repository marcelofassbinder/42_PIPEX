/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:45:32 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/10 19:43:51 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/**
 * Frees the memory allocated for the pipex_b structure and exits the program.
 *
 * @param ppx The pipex_b structure to be freed.
 * @param error The error message to be displayed.
 * @param error_code The error code to be returned.
 */
void    free_and_exit_b(t_pipex_b *ppx, char *error, int error_code)
{
	free_array(ppx->path);
	perror(error);
	exit(error_code);
}

/**
 * Frees the memory allocated for the command and path, and handles error reporting.
 * 
 * @param ppx The pipex_b struct containing necessary information.
 * @param command The command array to be freed.
 * @param error The error message to be displayed.
 * @param error_code The error code to be returned.
 */
void	free_command(t_pipex_b *ppx, char **command, char *error, int error_code)
{
	free_array(ppx->path);
	perror(error);
	free_array(command);
	exit(error_code);
}
