/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcelo <marcelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:26:01 by marcelo           #+#    #+#             */
/*   Updated: 2024/04/02 21:20:15 by marcelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "ft_printf/ft_printf.h"
#include "stdio.h"
#include "sys/wait.h"
#include "fcntl.h"
#include "errno.h"

typedef struct	s_pipex
{
	int pid;
	int end[2];
}				t_pipex;

#endif