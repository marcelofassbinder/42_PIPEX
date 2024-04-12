/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:21:08 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/10 19:53:03 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * @brief Exits the program with an error message and error code.
 *
 * @param error The error message to display.
 * @param error_code The error code to exit with.
 */
void	error_exit(char *error, int error_code)
{
	ft_printf(2, "%s", error);
	exit(error_code);
}

/**
 * @brief Frees a dynamically allocated array of strings.
 * 
 * This function frees the memory allocated for each string in the array,
 * as well as the memory allocated for the array itself.
 * 
 * @param array The array of strings to be freed.
 */
void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

/**
 * Frees the resources allocated for the pipex structure and exits the program.
 * 
 * @param ppx The pipex structure.
 * @param error The error message to display.
 * @param error_code The error code to exit with.
 */
void	free_and_exit(t_pipex *ppx, char *error, int error_code)
{
	perror(error);
	free_array(ppx->path);
	free_array(ppx->cmd1);
	free_array(ppx->cmd2);
	exit(error_code);
}
