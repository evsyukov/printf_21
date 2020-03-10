/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 15:05:48 by smanta            #+#    #+#             */
/*   Updated: 2020/02/08 15:05:52 by smanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t						print_char_n(char c, int num)
{
	size_t	len;

	len = 0;
	if (num >= 0)
	{
		len = num;
		while (num--)
			write(1, &c, 1);
	}
	return (len);
}

static long long			get_ll_with_length(t_convs *p_convs, int ival)
{
	long long res;

	res = ival;
	if (p_convs->length == 0)
		res = p_convs->conversion == 'u' ? (unsigned int)res : res;
	else if (p_convs->length == 1)
		res = p_convs->conversion == 'u' ? (unsigned short)res : (short)res;
	else if (p_convs->length == 4)
		res = p_convs->conversion == 'u' ? (unsigned char)res : (char)res;
	return (res);
}

long long					get_arg(t_convs *p_convs, va_list *ap)
{
	int			ival;
	long long	llval;

	llval = 0;
	if (p_convs->length == 0 || p_convs->length == 1 || p_convs->length == 4)
	{
		ival = va_arg(*ap, int);
		llval = get_ll_with_length(p_convs, ival);
	}
	else if (p_convs->length == 2)
		llval = va_arg(*ap, long);
	else if (p_convs->length == 5)
		llval = va_arg(*ap, long long);
	return (llval);
}

static unsigned long long	get_ull_with_length(t_convs *p_convs,
												unsigned int ival)
{
	unsigned long long	res;

	res = ival;
	if (p_convs->length == 1)
		res = (unsigned short)res;
	else if (p_convs->length == 4)
		res = (unsigned char)res;
	return (res);
}

unsigned long long			get_uarg(t_convs *p_convs, va_list *ap)
{
	unsigned int		ival;
	unsigned long long	llval;

	llval = 0;
	if (p_convs->length == 0 || p_convs->length == 1 || p_convs->length == 4)
	{
		ival = va_arg(*ap, int);
		llval = get_ull_with_length(p_convs, ival);
	}
	else if (p_convs->length == 2)
		llval = va_arg(*ap, long);
	else if (p_convs->length == 5)
		llval = va_arg(*ap, long long);
	return (llval);
}
