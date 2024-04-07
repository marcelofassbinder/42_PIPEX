/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:25:52 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/07 17:49:50 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* char    **define_command(int argc, char **argv, int here_doc)
{
    char    **command;
    int     i;

    if (here_doc == 1)
    {
        command = ft_calloc(sizeof(char *), argc - 3);
        i = 0;
        while(i < argc - 3)
        {
            if (ft_strchr(argv[3 + i], 39) != NULL)
                command = ft_split_trim(argv[3 + i], 39);
            else
                command = ft_split(argv[3 + i], ' ');
            i++;
        }
    }
    if (here_doc == 0)
    {
        command = ft_calloc(sizeof(char *), argc - 4);
        i = 0;
        while(i < argc - 4)
        {
            if (ft_strchr(argv[2 + i], 39) != NULL)
                command[i] = ft_split_trim(argv[2 + i], 39);
            else
                command[i] = ft_split(argv[2 + i], ' ');
            i++;
        }
    }
    return (command);
} */
/* 
if (ft_strchr(argv[2], 39) != NULL)
		ppx.cmd1 = ft_split_trim(argv[2], 39);
	else
		ppx.cmd1 = ft_split(argv[2], ' '); */