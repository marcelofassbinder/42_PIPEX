/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:23:11 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/03 19:48:51 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_space(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;
	int		size;

	if (!s2)
		return((char *)s1);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *) malloc(sizeof(char) * size);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i++] = ' ';
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	free((void*)s1);
	return (result);
}
/* 
#include <stdio.h>

int	main(void)
{
	char 	s1[] = "Gremio ";
	char	s2[] = "campeao mundial";	

	printf("%s", ft_strjoin(s1, s2));
} */
