/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letspars_what.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:14:35 by clashund          #+#    #+#             */
/*   Updated: 2020/02/06 12:14:37 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	letspars_flags(const char *fmt, size_t index, t_convs *p_convs)
{
	while (is_flag(fmt[index]))
	{
		if (fmt[index] == '#')
			p_convs->sharp = 1;
		else if (fmt[index] == '0')
			p_convs->zero = 1;
		else if (fmt[index] == '-')
			p_convs->minus = 1;
		else if (fmt[index] == ' ')
			p_convs->space = 1;
		else if (fmt[index] == '+')
			p_convs->plus = 1;
		else
			return (0);
		++index;
	}
	return (index);
}

size_t	letspars_width(const char *fmt, size_t index,
		t_convs *p_convs, va_list *ap)
{
	if (fmt[index] == '\0')
		return (0);
	if (fmt[index] == '*')
	{
		p_convs->width = va_arg(*ap, int);
		if (p_convs->width < 0)
		{
			p_convs->width = -p_convs->width;
			p_convs->minus = 1;
		}
		++index;
		if (fmt[index] < 48 || fmt[index] > 57)
			return (index);
	}
	p_convs->width = 0;
	while (fmt[index] > 47 && fmt[index] < 58)
		p_convs->width = p_convs->width * 10 + (fmt[index++] - 48);
	return (index);
}

size_t	letspars_precision(const char *fmt, size_t index,
		t_convs *p_convs, va_list *ap)
{
	if (fmt[index] == '\0')
		return (0);
	if (fmt[index] == '*')
	{
		p_convs->precision = va_arg(*ap, int);
		if (p_convs->precision < 0)
			p_convs->precision = -1;
		return (++index);
	}
	while (fmt[index] > 47 && fmt[index] < 58)
		p_convs->precision = p_convs->precision * 10 + (fmt[index++] - 48);
	return (index);
}

size_t	letspars_length(const char *fmt, size_t index, t_convs *p_convs)
{
	if (fmt[index] == '\0')
		return (0);
	if (fmt[index] == 'h')
		p_convs->length = 1;
	if (fmt[index] == 'l')
		p_convs->length = 2;
	if (fmt[index] == 'L')
		p_convs->length = 3;
	if (fmt[index] == 'h' && fmt[index + 1] == 'h')
		p_convs->length = 4;
	if (fmt[index] == 'l' && fmt[index + 1] == 'l')
		p_convs->length = 5;
	return (p_convs->length <= 3 ? index + 1 : index + 2);
}

size_t	letspars_conversion(const char *fmt, size_t index, t_convs *p_convs)
{
	if (fmt[index] == '\0')
		return (0);
	if (is_conversion(fmt[index]))
		p_convs->conversion = fmt[index++];
	return (index);
}
