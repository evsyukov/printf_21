/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:13:51 by clashund          #+#    #+#             */
/*   Updated: 2020/02/06 12:13:53 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_numlen_base(unsigned long long num, int base)
{
	int	len;

	len = 0;
	while ((num /= base))
		len++;
	return (len + 1);
}

char		*ft_ulltoa_base(unsigned long long n, int b)
{
	char	*str_num;
	int		len;

	len = ft_numlen_base(n, b);
	if ((str_num = ft_strnew(len)))
	{
		str_num[len] = '\0';
		while (len--)
		{
			if (b < 10)
				str_num[len] = n % b + '0';
			else
				str_num[len] = n % b >= 10 ? (n % b) - 10 + 'A' : (n % b) + '0';
			n /= b;
		}
	}
	return (str_num);
}
