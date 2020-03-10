/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:09:11 by clashund          #+#    #+#             */
/*   Updated: 2020/02/06 12:09:16 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_numlen_base(long long num, int base)
{
	int	len;

	len = num < 0 ? 1 : 0;
	while ((num /= base))
		len++;
	return (len + 1);
}

char		*ft_lltoa_base(long long n, int b)
{
	char				*str_num;
	int					len;
	int					dig;
	unsigned long long	l;

	len = ft_numlen_base(n, b);
	dig = (n < 0) ? 1 : 0;
	l = (n < 0) ? -n : n;
	if ((str_num = ft_strnew(len)))
	{
		str_num[len] = '\0';
		while (len--)
		{
			if (b < 10)
				str_num[len] = l % b + '0';
			else
				str_num[len] = l % b >= 10 ? (l % b) - 10 + 'A' : (l % b) + '0';
			l /= b;
		}
		if (dig)
			str_num[0] = '-';
	}
	return (str_num);
}
