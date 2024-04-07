/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:18:57 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/07 18:36:48 by mfassbin         ###   ########.fr       */
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
    char        **path;
}               t_pipex_b;

t_pipex_b   init_bonus(int argc, char **argv, char **envp);
void	last_process(t_pipex_b *ppx, char **argv, int argc, int i, char **envp);
void	mid_process(t_pipex_b *ppx, int i, char **argv, char **envp);
void	first_process(t_pipex_b *ppx, char **argv, int i, char **envp);
void	exec_command(t_pipex_b *ppx, int i, char **argv, char **envp);
int here_doc(char **argv);

#endif
