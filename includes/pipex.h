/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:39:00 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/12 12:48:02 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "stdio.h"
# include "sys/wait.h"
# include "fcntl.h"

# define EXIT_COMMAND 127

// * * * STRUCT * * *

typedef struct s_pipex
{
	int		pid;
	int		fd[2];
	char	**cmd1;
	char	**cmd2;
	char	**path;
}				t_pipex;

// * * * ERROR.C * * * 

void	error_exit(char *error, int error_code);
void	free_and_exit(t_pipex *ppx, char *error, int error_code);
void	free_array(char **array);

// * * * UTILS.C * * * 

void	exchange_fd(t_pipex *ppx, int file, char process);
void	exec_process(t_pipex *ppx, char **envp, char c);
char	**ft_path(char **envp);
char	**ft_split_trim(char *str, char c);
void	execve_call(t_pipex *ppx, int i, char **cmd, char **envp);

// * * * MAIN.C * * * 

void	handle_input(int argc, char **argv);
void	child_process(t_pipex *ppx, char *file, char **envp);
void	parent_process(t_pipex *ppx, char *file, char **envp);
t_pipex	init_struct(char **argv, char **envp);

#endif