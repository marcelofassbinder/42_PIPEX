/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:30:59 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/12 11:28:38 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(int fd, long nbr, char *base)
{
	long		len;
	int			count;

	len = (long)ft_len(base);
	count = 0;
	if (nbr < 0)
	{
		write (fd, "-", 1);
		return (ft_putnbr_base(fd, -nbr, base) + 1);
	}
	else if (nbr < len)
		return (write (fd, &base[nbr], 1));
	else
	{
		count = ft_putnbr_base(fd, nbr / len, base);
		return (count + ft_putnbr_base(fd, nbr % len, base));
	}
}
/* 
#include <stdio.h>

int	main ()
{
	int	a;
	int	c;

	a = -4682;
	c = ft_putnbr_base(a, "0123456789abcdef");
	printf("\n %i\n", c);
	printf("%x\n", a);
} */