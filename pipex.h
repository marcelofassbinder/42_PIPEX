/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:39:00 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/04 15:35:18 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "libft/libft.h"
#include "stdio.h"
#include "sys/wait.h"
#include "fcntl.h"
#include "errno.h"

typedef struct	s_pipex
{
	int     pid;
	int     fd[2];
    char    **cmd1;
    char    **cmd2;
    char    **path;
}				t_pipex;

// FREE.C
void    free_and_exit(t_pipex *ppx, char *error);
void	free_array(char **cmd);

//UTILS.C
void	exchange_fd(t_pipex *ppx, int file, char process);
void	exec_process(t_pipex *ppx, char **envp, char c);
char    **ft_path(char **envp);
t_pipex init_struct(char **argv, char **envp);
char    **ft_split_trim(char *str, char c);

//MAIN.C
void	child_process(t_pipex *ppx, char *file, char **envp);
void	parent_process(t_pipex *ppx, char *file, char **envp);

#endif