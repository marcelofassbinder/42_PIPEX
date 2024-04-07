/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:18:57 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/07 13:48:50 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

#include "../source/pipex.h"

typedef struct  s_pipex_b
{
    int         here_doc;
    int         processes;
    int         pid;
    int         **pipes;
    int         **commands;
    char        **path;
}               t_pipex_b;

char    *define_command(t_pipex_b *ppx, char *cmd);

#endif
