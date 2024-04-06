/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:18:57 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/06 18:05:39 by mfassbin         ###   ########.fr       */
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
}               t_pipex_b;

#endif
