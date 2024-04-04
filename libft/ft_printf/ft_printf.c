/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:38:36 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/03 16:37:10 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(int fd, const char *s, ...)
{
	va_list	args;
	int		count;

	va_start(args, s);
	count = 0;
	while (*s)
	{
		if (*s == '%')
			count += ft_print_format(fd, *(++s), args);
		else
			count += write(fd, s, 1);
		s++;
	}
	va_end (args);
	return (count);
}
/* 
#include <stdio.h>

int main(void)
{
	ft_printf("%i\n", -34);
	printf("%u\n", -34);
} */
