/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrull.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:11:46 by clashund          #+#    #+#             */
/*   Updated: 2020/02/06 12:11:47 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long long	ft_pow10(size_t p)
{
	long long	res;

	res = 1;
	while (p--)
		res *= 10;
	return (res);
}

static size_t				ft_getlen(unsigned long long n)
{
	size_t		len;

	len = 1;
	while ((n / 10) != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void					printch(const size_t *len,
		unsigned long long *pow_10, char *c, unsigned long long *n)
{
	*pow_10 = ft_pow10(*len);
	*c = 48 + *n / *pow_10;
	write(1, c, 1);
	*n = *n % *pow_10;
}

size_t						ft_putnbrull(unsigned long long n)
{
	size_t				res;
	size_t				len;
	unsigned long long	pow_10;
	char				c;

	res = 0;
	len = ft_getlen(n);
	res = res + len;
	while (len--)
		printch(&len, &pow_10, &c, &n);
	return (res);
}
