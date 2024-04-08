/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:18:57 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/08 16:57:13 by mfassbin         ###   ########.fr       */
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
    int         fd[2];
    char        **path;
}               t_pipex_b;

t_pipex_b init_bonus(int argc, char **argv, char **envp);
void	exec_command(t_pipex_b *ppx, int i, char **argv, char **envp);
int here_doc(char **argv);
void	handle_input_b(int argc, char **argv);

#endif
