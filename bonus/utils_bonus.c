/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:25:52 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/07 13:48:48 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//funcao que retorna o comando, usada na exec_command
char    *define_command(t_pipex_b *ppx, char *cmd)
{
    char    *command;

    if (ft_strchr(cmd, 39) != NULL)
        command = ft_split_trim(cmd, 39);
    else
        command = ft_split(cmd, ' ');
    
}
/* 
if (ft_strchr(argv[2], 39) != NULL)
		ppx.cmd1 = ft_split_trim(argv[2], 39);
	else
		ppx.cmd1 = ft_split(argv[2], ' '); */