/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:45:32 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/09 21:24:07 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void    free_and_exit_b(t_pipex_b *ppx, char *error, int error_code)
{
	free_array(ppx->path);
	perror(error);
	exit(error_code);
}