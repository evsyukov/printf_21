/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letsprint_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:15:14 by clashund          #+#    #+#             */
/*   Updated: 2020/02/06 12:15:16 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	print_spaces(t_convs *p_convs)
{
	size_t	res;
	int		num_spaces;

	res = 0;
	num_spaces = p_convs->width - 1;
	if (p_convs->zero == 1)
		num_spaces = 0;
	while (num_spaces-- > 0)
	{
		write(1, " ", 1);
		++res;
	}
	return (res);
}

static size_t	print_value(t_convs *p_convs)
{
	size_t	res;
	int		num;

	res = 0;
	num = 1;
	if (p_convs->zero == 1)
		while (p_convs->width - num++ > 0)
		{
			write(1, "0", 1);
			++res;
		}
	write(1, "%", 1);
	return (++res);
}

size_t			letsprint_percent(t_convs *p_convs, va_list *ap)
{
	size_t	res;

	ap = NULL;
	res = 0;
	if (p_convs->zero == 1 && (p_convs->precision != -1 || p_convs->minus == 1))
		p_convs->zero = 0;
	if (p_convs->width == 0)
	{
		write(1, "%", 1);
		return (1);
	}
	else if (p_convs->minus == 0)
	{
		res += print_spaces(p_convs);
		res += print_value(p_convs);
	}
	else
	{
		res += print_value(p_convs);
		res += print_spaces(p_convs);
	}
	return (res);
}
