/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:18:57 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/12 13:08:18 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

// * * * STRUCT * * * 

typedef struct s_pipex_b
{
	int			here_doc;
	int			processes;
	int			pid;
	int			fd[2];
	char		**path;
	char		**envp;
}				t_pipex_b;

// * * * PIPEX_BONUS.C * * *

int			open_infile(t_pipex_b *ppx, char **argv);
void		child_process_b(t_pipex_b *ppx, int *fd_redir, int i, char **argv);
void		parent_process_b(t_pipex_b *ppx, int *fd_redir);
void		last_process(t_pipex_b *ppx, int i, int argc, char **argv);

// * * * ERROR_BONUS.C * * * 

void		free_and_exit_b(t_pipex_b *ppx, char *error, int error_code);
void		free_command(t_pipex_b *ppx, char **command, char *error,
				int error_code);

// * * * UTILS_BONUS.C * * * 

t_pipex_b	init_bonus(int argc, char **argv, char **envp);
void		exec_command(t_pipex_b *ppx, int i, char **argv);
int			here_doc(t_pipex_b *ppx, char **argv);
char		**define_command(t_pipex_b *ppx, int i, char **argv);

#endif
