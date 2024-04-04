/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:23:17 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/03 16:42:09 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(int fd, char *s)
{
	int	count;

	if (!s)
		return (write (fd, "(null)", 6));
	count = 0;
	while (s[count])
	{
		write (fd, &s[count], 1);
		count++;
	}
	return (count);
}
